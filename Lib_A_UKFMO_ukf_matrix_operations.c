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

ukfmo_fnc_status_e
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
/*#### |End  | <-- Секция - "Описание глобальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание локальных функций" #####################*/
/*#### |End  | <-- Секция - "Описание локальных функций" #####################*/


/*#### |Begin| --> Секция - "Обработчики прерываний" #########################*/
/*#### |End  | <-- Секция - "Обработчики прерываний" #########################*/

/*############################################################################*/
/*############################ END OF FILE  ##################################*/
/*############################################################################*/
