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

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      22-апр-2019
 *
 * @brief    Функция выполняет инициализацию структуры матрицы
 *
 * @param[out] 	*p_s:		Указатель на структуру, инициализацию
 * 							которой необходимо выполнить
 * @param[in] 	rowNumb:	Количество строк матрицы
 * @param[in]  	columnNumb:	Количество столбцов матрицы
 * @param[in] 	*pMatrix:	указатель на область памяти, в
 * 							которой будет размещена матрицы
 *
 * @return  Статус операции
 *                @see ukfmo_fnc_status_e
 */
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
UKFMO_MatrixOnes(
#if defined(__UKFMO_USE_ARM_MATH__)
	#if (__UKFMO_FPT_SIZE__)    == 4
		arm_matrix_instance_f32 *pSrc_s
	#elif (__UKFMO_FPT_SIZE__)  == 8
		arm_matrix_instance_f64 *pSrc_s
	#endif
#else
	ukfmo_matrix_s *pSrc_s
#endif
)
{
	#if defined(__UKFMO_USE_ARM_MATH__)
	size_t i;
	for (i = 0; i < pSrc_s->numCols * pSrc_s->numRows; i++)
	{
		pSrc_s->pData[i] = (__UKFMO_FPT__) 1.0;
	}
	#else
	size_t i;
	for (i = 0; i < pSrc_s->columnNumb * pSrc_s->rowNumb; i++)
	{
		pSrc_s->pData[i] = (__UKFMO_FPT__) 1.0;
	}
	#endif

	return (UKFMO_OK);
}

ukfmo_fnc_status_e
UKFMO_MatrixIdentity(
#if defined(__UKFMO_USE_ARM_MATH__)
	#if (__UKFMO_FPT_SIZE__)    == 4
		arm_matrix_instance_f32 *pSrc_s
	#elif (__UKFMO_FPT_SIZE__)  == 8
		arm_matrix_instance_f64 *pSrc_s
	#endif
#else
	ukfmo_matrix_s *pSrc_s
#endif
)
{
	#if defined(__UKFMO_USE_ARM_MATH__)
	__UKFMO_FPT__ * const pDst = (__UKFMO_FPT__ *)pSrc_s->pData;
	const size_t nCol = pSrc_s->numCols;
	size_t eIdx;

	ukfmo_fnc_status_e status_e = UKFMO_OK;
	if (pSrc_s->numRows == nCol)
	{
		pDst[0] = 1;

		for (eIdx = 1; eIdx < pSrc_s->numRows * pSrc_s->numCols; eIdx++)
		{
			const size_t cmpLeft = (size_t)(eIdx / nCol);

			pDst[eIdx] = eIdx < nCol ? 0 : cmpLeft == eIdx % (cmpLeft * nCol) ?  1 : 0;
		}
	}
	else
	{
		status_e = UKFMO_SIZE_MISMATCH;
	}

	#else
	__UKFMO_FPT__ * const pDst = (__UKFMO_FPT__ *)pSrc_s->pData;
	const size_t nCol = pSrc_s->columnNumb;
	size_t eIdx;

	ukfmo_fnc_status_e status_e = UKFMO_OK;
	if (pSrc_s->rowNumb == nCol)
	{
		pDst[0] = 1;

		for (eIdx = 1; eIdx < pSrc_s->rowNumb * pSrc_s->columnNumb; eIdx++)
		{
			const size_t cmpLeft = (size_t)(eIdx / nCol);

			pDst[eIdx] = eIdx < nCol ? 0 : cmpLeft == eIdx % (cmpLeft * nCol) ?  1 : 0;
		}
	}
	else
	{
		status_e = UKFMO_SIZE_MISMATCH;
	}
	#endif

	return (status_e);
}

__UKFMO_FORCE_INLINE ukfmo_fnc_status_e
UKFMO_MatrixZeros(
#if defined(__UKFMO_USE_ARM_MATH__)
	#if (__UKFMO_FPT_SIZE__)    == 4
		arm_matrix_instance_f32 *pSrc_s
	#elif (__UKFMO_FPT_SIZE__)  == 8
		arm_matrix_instance_f64 *pSrc_s
	#endif
#else
	ukfmo_matrix_s *pSrc_s
#endif
)
{
	#if defined(__UKFMO_USE_ARM_MATH__)
	memset(
		(void*) pSrc_s->pData,
		0,
		sizeof(__UKFMO_FPT_SIZE__) * pSrc_s->numCols * pSrc_s->numCols);
	#else
	memset(
		(void*) pSrc_s->pData,
		0,
		sizeof(__UKFMO_FPT_SIZE__) * pSrc_s->columnNumb * pSrc_s->rowNumb);
	#endif

	return (UKFMO_OK);
}

__attribute__((optimize("Ofast")))  __UKFMO_FORCE_INLINE ukfmo_fnc_status_e UKFMO_MatrixInverse(
#if defined(__UKFMO_USE_ARM_MATH__)
	#if (__UKFMO_FPT_SIZE__)    == 4
		arm_matrix_instance_f32 *pSrc_s,
		arm_matrix_instance_f32 *pDst_s
	#elif (__UKFMO_FPT_SIZE__)  == 8
		arm_matrix_instance_f64 *pSrc_s,
		arm_matrix_instance_f64 *pDst_s
	#endif
#else
	ukfmo_matrix_s *pSrc_s,
	ukfmo_matrix_s *pDst_s
#endif
)
{
	#if defined(__UKFMO_USE_ARM_MATH__)
	arm_status status_e;
	#if (__UKFMO_FPT_SIZE__) == 4
	status_e = arm_mat_inverse_f32(pSrc_s, pDst_s);
	#else
	status_e = arm_mat_inverse_f64(pSrc_s, pDst_s);
	#endif
	#else
	ukfmo_fnc_status_e status_e = UKFMO_OK;
	const size_t nrow = pSrc_s->rowNumb;
	const size_t ncol = pSrc_s->columnNumb;
	size_t j, i;
	size_t k = 0;
	size_t l = 0;
	__UKFMO_FPT__ s = 0;
	__UKFMO_FPT__ t = 0;

	if (nrow == ncol)
	{
		for (j = 0; j < nrow; j++)
		{
			for (i = j; i < nrow; i++)
			{
				if (0 != pSrc_s->pData[ncol * i + j])
				{
					for (k = 0; k < nrow; k++)
					{
						s = pSrc_s->pData[ncol * j + k];
						pSrc_s->pData[ncol * j + k] = pSrc_s->pData[ncol * i + k];
						pSrc_s->pData[ncol * i + k] = s;

						s = pDst_s->pData[ncol * j + k];
						pDst_s->pData[ncol * j + k] = pDst_s->pData[ncol * i + k];
						pDst_s->pData[ncol * i + k] = s;
					}

					t = 1 / pSrc_s->pData[ncol * j + j];

					for (k = 0; k < nrow; k++)
					{
						pSrc_s->pData[ncol * j + k] = t * pSrc_s->pData[ncol * j + k];
						pDst_s->pData[ncol * j + k] = t * pDst_s->pData[ncol * j + k];
					}

					for (l = 0; l < nrow; l++)
					{
						if (l != j)
						{
							t = -pSrc_s->pData[ncol * l + j];
							for (k = 0; k < nrow; k++)
							{
								pSrc_s->pData[ncol * l + k] += t *  pSrc_s->pData[ncol * j + k];
								pDst_s->pData[ncol * l + k] += t *  pDst_s->pData[ncol * j + k];
							}
						}
					}
				}
				break;
			}
			if (0 == pSrc_s->pData[ncol * l + k])
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

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      22-апр-2019
 *
 * @brief   Функция выполняет разложение Холецкого квадратной матрицы
 * @param[in]   *pSrcMatrix:    Указатель на нулевой элемент массива (двумерной
 *                              квадратной матрицы), разложение которой необходимо
 *                              выполнить
 * @param[out]  *pDstMatrix:    Указатель на нулевой элемент массива (двумерной
 *                              квадратной матрицы) в который будет записан
 *                              результат разложения Холецкого
 * @param[in]   rowOrColumnNumb:    Количество строк или столбцов квадратной
 *                                  матрицы, разложение которой необходимо
 *                                  выполнить
 * @return  None
 */
ukfmo_fnc_status_e __UKFMO_OPTIMIZE_OFAST
UKFMO_GetCholeskyLow(
#if defined(__UKFMO_USE_ARM_MATH__)
	#if (__UKFMO_FPT_SIZE__)    == 4
		arm_matrix_instance_f32 *pSrc_s
	#elif (__UKFMO_FPT_SIZE__)  == 8
		arm_matrix_instance_f64 *pSrc_s
	#endif
#else
	ukfmo_matrix_s *pSrc_s
#endif
)
{
	ukfmo_fnc_status_e status_e = UKFMO_OK;
	__UKFMO_FPT__ * const pSrcL = pSrc_s->pData;
	size_t col, row;
	int32_t tmp;
	__UKFMO_FPT__ sum = 0;
	#if defined(__UKFMO_USE_ARM_MATH__)
	const size_t nrow = pSrc_s->numRows;
	const size_t ncol = pSrc_s->numCols;
	#else
	const size_t nrow = pSrc_s->rowNumb;
	const size_t ncol = pSrc_s->columnNumb;
	#endif

	if (ncol == nrow)
	{
		const size_t mtxSize = nrow;

		for (col = 0; col < mtxSize; col++)
		{
			for (row = 0; row < mtxSize; row++)
			{
				sum = pSrcL[mtxSize * col + row];

				for (tmp = (int32_t)(col - 1); tmp >= 0; tmp--)
				{
					sum -= pSrcL[mtxSize * row + tmp] * pSrcL[mtxSize * col + tmp];
				}

				pSrcL[ncol * row + col] = (row == col) ? __UKFMO_sqrt(sum) : (row > col) ? (sum / pSrcL[ncol * col + col]) : 0;


//				if ((row == col) && (sum <= 0))
//				{
//					status_e = UKFMO_NOT_POS_DEFINED;
//				}
			}
		}
	}
//	else
//	{
//		status_e = UKFMO_NOT_SQUARE;
//	}

	return (status_e);
}
/*#### |End  | <-- Секция - "Описание глобальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание локальных функций" #####################*/
/*#### |End  | <-- Секция - "Описание локальных функций" #####################*/


/*#### |Begin| --> Секция - "Обработчики прерываний" #########################*/
/*#### |End  | <-- Секция - "Обработчики прерываний" #########################*/

/*############################################################################*/
/*############################ END OF FILE  ##################################*/
/*############################################################################*/
