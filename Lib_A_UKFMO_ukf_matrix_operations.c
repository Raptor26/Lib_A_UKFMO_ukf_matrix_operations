/**
 * @file   	%<%NAME%>%.%<%EXTENSION%>%
 * @author 	%<%USER%>%
 * @version
 * @date 	%<%DATE%>%, %<%TIME%>%
 * @brief
 */


/*#### |Begin| --> Секция - "Include" ########################################*/
#include "Lib_A_UKFMO_ukf_matrix_operations.h"
/*#### |End  | <-- Секция - "Include" ########################################*/


/*#### |Begin| --> Секция - "Глобальные переменные" ##########################*/
/*#### |End  | <-- Секция - "Глобальные переменные" ##########################*/


/*#### |Begin| --> Секция - "Локальные переменные" ###########################*/
/*#### |End  | <-- Секция - "Локальные переменные" ###########################*/


/*#### |Begin| --> Секция - "Прототипы локальных функций" ####################*/
/*#### |End  | <-- Секция - "Прототипы локальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание глобальных функций" ####################*/
ukfmo_fnc_status_e
UKFMO_MatrixInit(
#if defined(__UKFMO_USE_ARM_MATH__)
	#if (__UKFMO_FPT_SIZE__) 	== 4
		arm_matrix_instance_f32 *p_s,
	#elif (__UKFMO_FPT_SIZE__) 	== 8
		arm_matrix_instance_f64 *p_s,
	#endif
#else
	ukfmo_matrix_s *p_s,
#endif
	size_t rowNumb,
	size_t columnNumb,
	__UKFMO_FPT__ *pMatrix)
{
	#if defined(__UKFMO_USE_ARM_MATH__)
	#if( __UKFMO_FPT_SIZE__) == 4
	arm_mat_init_f32(
		p_s,
		rowNumb,
		columnNumb,
		pMatrix);
	#else
	arm_mat_init_f64(
		p_s,
		rowNumb,
		columnNumb,
		pMatrix);
	#endif
	#else
	p_s->rowNumb 		= rowNumb;
	p_s->columnNumb 	= columnNumb;
	p_s->pData 			= pMatrix;
	#endif
	return (UKFMO_OK);
}

ukfmo_fnc_status_e
UKFMO_MatrixTranspose(
#if defined(__UKFMO_USE_ARM_MATH__)
	#if (__UKFMO_FPT_SIZE__) 	== 4
		arm_matrix_instance_f32 *pSrc,
		arm_matrix_instance_f32 *pDst
	#elif (__UKFMO_FPT_SIZE__) 	== 8
		arm_matrix_instance_f64 *pSrc,
		arm_matrix_instance_f64 *pDst
	#endif
#else
	ukfmo_matrix_s *pSrc,
	ukfmo_matrix_s *pDst
#endif
)
{
	#if defined(__UKFMO_USE_ARM_MATH__)
	arm_status status_e;
	#if( __UKFMO_FPT_SIZE__) == 4
	status_e = arm_mat_trans_f32(pSrc, pDst);
	#else
	status_e = arm_mat_trans_f64(pSrc, pDst);
	#endif

	#else
	/* -->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
	__UKFMO_FPT__ const * const pSrcL 	= (__UKFMO_FPT__ *)pSrc->pData;
	__UKFMO_FPT__ * const pDstL 		= (__UKFMO_FPT__ *)pDst->pData;
	const uint16_t nRowSrcL = pSrc->rowNumb;
	const uint16_t nColSrcL = pSrc->columnNumb;
	const uint16_t nRowDstL = pDst->rowNumb;
	const uint16_t nColDstL = pDst->columnNumb;
	uint16_t row, col;

	ukfmo_fnc_status_e status_e = UKFMO_OK;
	if (nRowSrcL == nColDstL || nColSrcL == nRowDstL)
	{
		for (row = 0; row < nRowDstL; row++)
		{
			for (col = 0; col < nColDstL; col++)
			{
				pDstL[nColDstL * row + col] = pSrcL[nColSrcL * col + row];
			}
		}
	}
	else
	{
		status_e = UKFMO_SIZE_MISMATCH;
	}
	#endif /* defined(__UKFMO_USE_ARM_MATH__) */
	/* --<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< */
	return (status_e);
}

ukfmo_fnc_status_e
UKFMO_MatrixInverse(
#if defined(__UKFMO_USE_ARM_MATH__)
	#if (__UKFMO_FPT_SIZE__) 	== 4
		arm_matrix_instance_f32 *pSrc,
		arm_matrix_instance_f32 *pDst
	#elif (__UKFMO_FPT_SIZE__) 	== 8
		arm_matrix_instance_f64 *pSrc,
		arm_matrix_instance_f64 *pDst
	#endif
#else
	ukfmo_matrix_s *pSrc,
	ukfmo_matrix_s *pDst
#endif
)
{
	#if defined(__UKFMO_USE_ARM_MATH__)
	arm_status status_e;
	#if (__UKFMO_FPT_SIZE__) == 4
	status_e = arm_mat_inverse_f32(pSrc, pDst);
	#else
	status_e = arm_mat_inverse_f64(pSrc, pDst);
	#endif
	#else
	ukfmo_fnc_status_e status_e = UKFMO_OK;
	const uint8_t nrow = pSrc->rowNumb;
	const uint8_t ncol = pSrc->columnNumb;
	uint8_t j, i;
	uint8_t k = 0;
	uint8_t l = 0;
	__UKFMO_FPT__ s = 0;
	__UKFMO_FPT__ t = 0;

	if (nrow == ncol)
	{
		for (j = 0; j < nrow; j++)
		{
			for (i = j; i < nrow; i++)
			{
				if (0 != pSrc->pData[ncol * i + j])
				{
					for (k = 0; k < nrow; k++)
					{
						s = pSrc->pData[ncol * j + k];
						pSrc->pData[ncol * j + k] = pSrc->pData[ncol * i + k];
						pSrc->pData[ncol * i + k] = s;

						s = pDst->pData[ncol * j + k];
						pDst->pData[ncol * j + k] = pDst->pData[ncol * i + k];
						pDst->pData[ncol * i + k] = s;
					}

					t = 1 / pSrc->pData[ncol * j + j];

					for (k = 0; k < nrow; k++)
					{
						pSrc->pData[ncol * j + k] = t * pSrc->pData[ncol * j + k];
						pDst->pData[ncol * j + k] = t * pDst->pData[ncol * j + k];
					}

					for (l = 0; l < nrow; l++)
					{
						if (l != j)
						{
							t = -pSrc->pData[ncol * l + j];
							for (k = 0; k < nrow; k++)
							{
								pSrc->pData[ncol * l + k] += t *  pSrc->pData[ncol * j + k];
								pDst->pData[ncol * l + k] += t *  pDst->pData[ncol * j + k];
							}
						}
					}
				}
				break;
			}
			if (0 == pSrc->pData[ncol * l + k])
			{
				status_e = UKFMO_SINGULAR;
			}
		}
	}
	else
	{
		status_e = UKFMO_SIZE_MISMATCH;
	}
	#endif

	return (status_e);
}

ukfmo_fnc_status_e
UKFMO_MatrixMultiplication(
#if defined(__UKFMO_USE_ARM_MATH__)
	#if (__UKFMO_FPT_SIZE__) 	== 4
		arm_matrix_instance_f32 *pSrcA,
		arm_matrix_instance_f32 *pSrcB,
		arm_matrix_instance_f32 *pDst
	#elif (__UKFMO_FPT_SIZE__) 	== 8
		arm_matrix_instance_f64 *pSrcA,
		arm_matrix_instance_f64 *pSrcB,
		arm_matrix_instance_f64 *pDst
	#endif
#else
	ukfmo_matrix_s *pSrcA,
	ukfmo_matrix_s *pSrcB,
	ukfmo_matrix_s *pDst
#endif
)
{
	#if defined(__UKFMO_USE_ARM_MATH__)
	arm_status status_e;
	#if (__UKFMO_FPT_SIZE__) == 4
	status_e = arm_mat_mult_f32(pSrcA, pSrcB, pDst);
	#else
	status_e = arm_mat_mult_f64(pSrcA, pSrcB, pDst);
	#endif
	#else
	ukfmo_fnc_status_e status_e = UKFMO_OK;
	__UKFMO_FPT__ const * const pSrc1L 	= (__UKFMO_FPT__ *)pSrcA->pData;
	__UKFMO_FPT__ const * const pSrc2L 	= (__UKFMO_FPT__ *)pSrcB->pData;
	__UKFMO_FPT__ * const pDstL 		= (__UKFMO_FPT__ *)pDst->pData;
	uint8_t row, col, k;
	__UKFMO_FPT__ sum;

	if (pSrcA->columnNumb == pSrcB->rowNumb)
	{
		for (row = 0; row < pSrcA->rowNumb; row++)
		{
			for (col = 0; col < pSrcB->columnNumb; col++)
			{
				sum = 0;
				for (k = 0; k < pSrcA->columnNumb; k++)
				{
					sum += pSrc1L[pSrcA->columnNumb * row + k] * pSrc2L[pSrcB->columnNumb * k + col];
				}
				pDstL[pDst->columnNumb * row + col] = sum;
			}
		}
	}
	else
	{
		status_e = UKFMO_SIZE_MISMATCH;
	}
	#endif

	return (status_e);
}

ukfmo_fnc_status_e
UKFMO_MatrixMultScale(
#if defined(__UKFMO_USE_ARM_MATH__)
	#if (__UKFMO_FPT_SIZE__) 	== 4
		arm_matrix_instance_f32 *pSrc_s,
		__UKFMO_FPT__ 			scale,
		arm_matrix_instance_f32 *pDst_s
	#elif (__UKFMO_FPT_SIZE__) 	== 8
		arm_matrix_instance_f64 *pSrc_s,
		__UKFMO_FPT__ 			scale,
		arm_matrix_instance_f64 *pDst_s
	#endif
#else
	ukfmo_matrix_s *pSrc_s,
	__UKFMO_FPT__ 	scale,
	ukfmo_matrix_s *pDst_s
#endif
)
{
	#if defined(__UKFMO_USE_ARM_MATH__)
	arm_status status_e;
	#if (__UKFMO_FPT_SIZE__) == 4
	status_e = arm_mat_scale_f32(pSrc_s, scale, pDst_s);
	#else
	status_e = arm_mat_scale_f64(pSrc_s, scale, pDst_s);
	#endif
	#else

	ukfmo_fnc_status_e status_e = UKFMO_OK;
	__UKFMO_FPT__ *pDst = (__UKFMO_FPT__ *)pDst_s->pData;
	size_t eIdx;
	for (eIdx = 0; eIdx < pSrc_s->columnNumb * pSrc_s->rowNumb; eIdx++)
	{
		pDst[eIdx] *= scale;
	}
	#endif

	return (status_e);
}

ukfmo_fnc_status_e
UKMO_MatrixSubstraction(
#if defined(__UKFMO_USE_ARM_MATH__)
	#if (__UKFMO_FPT_SIZE__) 	== 4
		arm_matrix_instance_f32 *pSrcA,
		arm_matrix_instance_f32 *pSrcB,
		arm_matrix_instance_f32 *pDst
	#elif (__UKFMO_FPT_SIZE__) 	== 8
		arm_matrix_instance_f64 *pSrcA,
		arm_matrix_instance_f64 *pSrcB,
		arm_matrix_instance_f64 *pDst
	#endif
#else
	ukfmo_matrix_s *pSrcA,
	ukfmo_matrix_s *pSrcB,
	ukfmo_matrix_s *pDst
#endif
)
{
	#if defined(__UKFMO_USE_ARM_MATH__)
	arm_status status_e;
	#if (__UKFMO_FPT_SIZE__) == 4
	status_e = arm_mat_sub_f32(pSrcA, pSrcB, pDst);
	#else
	status_e = arm_mat_sub_f64(pSrcA, pSrcB, pDst);
	#endif
	#else
	ukfmo_fnc_status_e status_e = UKFMO_OK;
	__UKFMO_FPT__ * const pDstL 		= (__UKFMO_FPT__ *)pDst->pData;
	__UKFMO_FPT__ const * const pSrcA_ 	= (__UKFMO_FPT__ *)pSrcA->pData;
	__UKFMO_FPT__ const * const pSrcB_ 	= (__UKFMO_FPT__ *)pSrcB->pData;
	if ((pSrcA->columnNumb == pSrcB->columnNumb) && (pSrcA->rowNumb == pSrcB->rowNumb))
	{
		size_t eIdx;
		for (eIdx = 0; eIdx < pSrcA->columnNumb * pSrcA->rowNumb; eIdx++)
		{
			pDstL[eIdx] = pSrcA_[eIdx] - pSrcB_[eIdx];
		}
	}
	else
	{
		status_e = UKFMO_SIZE_MISMATCH;
	}
	#endif

	return (status_e);
}

ukfmo_fnc_status_e
UKMO_MatrixAdition(
#if defined(__UKFMO_USE_ARM_MATH__)
	#if (__UKFMO_FPT_SIZE__) 	== 4
		arm_matrix_instance_f32 *pSrcA,
		arm_matrix_instance_f32 *pSrcB,
		arm_matrix_instance_f32 *pDst
	#elif (__UKFMO_FPT_SIZE__) 	== 8
		arm_matrix_instance_f64 *pSrcA,
		arm_matrix_instance_f64 *pSrcB,
		arm_matrix_instance_f64 *pDst
	#endif
#else
	ukfmo_matrix_s *pSrcA,
	ukfmo_matrix_s *pSrcB,
	ukfmo_matrix_s *pDst
#endif
)
{
	#if defined(__UKFMO_USE_ARM_MATH__)
	arm_status status_e;
	#if (__UKFMO_FPT_SIZE__) == 4
	status_e = arm_mat_add_f32(pSrcA, pSrcB, pDst);
	#else
	status_e = arm_mat_add_f64(pSrcA, pSrcB, pDst);
	#endif
	#else
	ukfmo_fnc_status_e status_e = UKFMO_OK;
	__UKFMO_FPT__ * const pDstL 		= (__UKFMO_FPT__ *)pDst->pData;
	__UKFMO_FPT__ const * const pSrcA_ 	= (__UKFMO_FPT__ *)pSrcA->pData;
	__UKFMO_FPT__ const * const pSrcB_ 	= (__UKFMO_FPT__ *)pSrcB->pData;
	if ((pSrcA->columnNumb == pSrcB->columnNumb) && (pSrcA->rowNumb == pSrcB->rowNumb))
	{
		size_t eIdx;
		for (eIdx = 0; eIdx < pSrcA->columnNumb * pSrcA->rowNumb; eIdx++)
		{
			pDstL[eIdx] = pSrcA_[eIdx] + pSrcB_[eIdx];
		}
	}
	else
	{
		status_e = UKFMO_SIZE_MISMATCH;
	}
	#endif

	return (status_e);
}

/**
 * @brief	Функция выполняет разложение Холецкого квадратной матрицы
 * @param[in]	*pSrcMatrix:	Указатель на нулевой элемент массива (двумерной
 * 								квадратной матрицы), разложение которой необходимо
 * 								выполнить
 * @param[out]	*pDstMatrix:	Указатель на нулевой элемент массива (двумерной
 * 								квадратной матрицы) в который будет записан
 * 								результат разложения Холецкого
 * @param[in]	rowOrColumnNumb:	Количество строк или столбцов квадратной
 * 									матрицы, разложение которой необходимо
 * 									выполнить
 * @return	None
 */
void
UKMO_GetCholeskyLow(
	__UKFMO_FPT__ *pSrcMatrix,
	__UKFMO_FPT__ *pDstMatrix,
	size_t rowOrColumnNumb)
{
	size_t marixSize = rowOrColumnNumb * rowOrColumnNumb;
	__UKFMO_FPT__ dstMatrixTemp_a[marixSize];
	memset(
		dstMatrixTemp_a,
		0,
		marixSize);

	size_t i,
		   j;
	for (i = 0; i < rowOrColumnNumb; i++)
	{
		for (j = 0; j < (i + 1); j++)
		{
			__UKFMO_FPT__ s = 0;
			for (size_t k = 0; k < j; k++)
			{
				s += dstMatrixTemp_a[i * rowOrColumnNumb + k] * dstMatrixTemp_a[j * rowOrColumnNumb + k];
			}

			dstMatrixTemp_a[i * rowOrColumnNumb + j] =
				(i == j) ?
				__UKFMO_sqrt(pSrcMatrix[i * rowOrColumnNumb + i] - s) :
				(1.0 / dstMatrixTemp_a[j * rowOrColumnNumb + j] * (pSrcMatrix[i * rowOrColumnNumb + j] - s));
		}
	}

	memcpy(
		pDstMatrix,
		dstMatrixTemp_a,
		sizeof(dstMatrixTemp_a));
}
/*#### |End  | <-- Секция - "Описание глобальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание локальных функций" #####################*/
/*#### |End  | <-- Секция - "Описание локальных функций" #####################*/


/*#### |Begin| --> Секция - "Обработчики прерываний" #########################*/
/*#### |End  | <-- Секция - "Обработчики прерываний" #########################*/

/*############################################################################*/
/*############################ END OF FILE  ##################################*/
/*############################################################################*/
