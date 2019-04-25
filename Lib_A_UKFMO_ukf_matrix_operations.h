/**
 * @file    %<%NAME%>%.%<%EXTENSION%>%
 * @author  %<%USER%>%
 * @version
 * @date    %<%DATE%>%, %<%TIME%>%
 * @brief
 */


#ifndef LIB_A_UKFMO_UKF_MATRIX_OPERATIONS_H_
#define LIB_A_UKFMO_UKF_MATRIX_OPERATIONS_H_


/*#### |Begin| --> Секция - "Include" ########################################*/
/*==== |Begin| --> Секция - "C libraries" ====================================*/
#include "math.h"
#include "stdint.h"
#include "string.h"
/*==== |End  | <-- Секция - "C libraries" ====================================*/

/*==== |Begin| --> Секция - "MK peripheral libraries" ========================*/
#if defined (__UKFMO_USE_ARM_MATH__)
	#include "arm_math.h"
#endif
/*==== |End  | <-- Секция - "MK peripheral libraries" ========================*/

/*==== |Begin| --> Секция - "Extern libraries" ===============================*/
/*==== |End  | <-- Секция - "Extern libraries" ===============================*/
/*#### |End  | <-- Секция - "Include" ########################################*/


/*#### |Begin| --> Секция - "Определение констант" ###########################*/

/* |Begin| --> Секция определения типа числа с плавающей точкой ============= */
#if !defined (__UKFMO_FPT__)
	#error "Please, set __UKFMO_FPT__ float or double in macros list"
#endif

#if !defined (__UKFMO_FPT_SIZE__)
	#error "Please, set __UKFMO_FPT_SIZE__ 4 (that mean float) or 8 (that mean double) in macros list"
#endif

#if     __UKFMO_FPT_SIZE__ == 4
	#ifndef __UKFMO_sqrt
		#define __UKFMO_sqrt(x)       sqrtf(x)
	#endif
#elif   __UKFMO_FPT_SIZE__ == 8
	#ifndef __UKFMO_sqrt
		#define __UKFMO_sqrt(x)       sqrt(x)
	#endif
#else
	#error "Your compiler uses a non-standard floating point size"
#endif
/* |End  | <-- Секция определения типа числа с плавающей точкой ============= */

#if defined (__GNUC__)

	/* inline*/
	#ifndef __UKFMO_INLINE
		#define __UKFMO_INLINE          inline
	#endif

	/* static inline */
	#ifndef __UKFMO_STATIC_INLINE
		#define __UKFMO_STATIC_INLINE   static inline
	#endif

	/* always inline */
	#ifndef __UKFMO_ALWAYS_INLINE
		#define __UKFMO_ALWAYS_INLINE    inline __attribute__((always_inline)) static
	#endif
#ifndef __UKFMO_FORCE_INLINE
#define __UKFMO_FORCE_INLINE	inline __attribute__((always_inline))
#endif

#else
	#define __UKFMO_INLINE
	#define __UKFMO_STATIC_INLINE   static
	#define __UKFMO_ALWAYS_INLINE
#endif
/*#### |End  | <-- Секция - "Определение констант" ###########################*/


/*#### |Begin| --> Секция - "Определение типов" ##############################*/
typedef enum
{
	#if defined(__UKFMO_USE_ARM_MATH__)
	UKFMO_OK                 = ARM_MATH_SUCCESS,
	UKFMO_ARGUMENT_ERROR     = ARM_MATH_ARGUMENT_ERROR,
	UKFMO__LENGTH_ERROR      = ARM_MATH_LENGTH_ERROR,
	UKFMO_SIZE_MISMATCH      = ARM_MATH_SIZE_MISMATCH,
	UKFMO_NANINF             = ARM_MATH_NANINF,
	UKFMO_SINGULAR           = ARM_MATH_SINGULAR,
	UKFMO_TEST_FAULURE       = ARM_MATH_TEST_FAILURE,
	UKFMO_NOT_POS_DEFINED,
	UKFMO_NOT_SQUARE,
	#else
	UKFMO_OK                 = 0u,
	UKFMO_ERROR,
	UKFMO_SIZE_MISMATCH,
	UKFMO_SINGULAR,
	UKFMO_NOT_POS_DEFINED,
	UKFMO_NOT_SQUARE,
	#endif
} ukfmo_fnc_status_e;

typedef struct
{
	__UKFMO_FPT__   *pData;
	uint16_t        rowNumb;
	uint16_t        columnNumb;
}
#if defined (__GNUC__)
	__attribute__((__packed__))
#else
	#error "Please, define compiler"
#endif
ukfmo_matrix_s;
/*#### |End  | <-- Секция - "Определение типов" ##############################*/


/*#### |Begin| --> Секция - "Определение глобальных переменных" ##############*/
/*#### |End  | <-- Секция - "Определение глобальных переменных" ##############*/


/*#### |Begin| --> Секция - "Прототипы глобальных функций" ###################*/

extern ukfmo_fnc_status_e
UKFMO_MatrixInit(
#if defined(__UKFMO_USE_ARM_MATH__)
	#if (__UKFMO_FPT_SIZE__)    == 4
		arm_matrix_instance_f32 *p_s,
	#elif (__UKFMO_FPT_SIZE__)  == 8
		arm_matrix_instance_f64 *p_s,
	#endif
#else
	ukfmo_matrix_s *p_s,
#endif
	size_t rowNumb,
	size_t columnNumb,
	__UKFMO_FPT__ *pMatrix
)__attribute__ ((section(".itcmram")));

extern ukfmo_fnc_status_e
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
) __attribute__ ((section(".itcmram")));

extern ukfmo_fnc_status_e
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
) __attribute__ ((section(".itcmram")));


/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      22-апр-2019
 *
 * @brief   Функция выполняет сложение двух матриц
 *
 * @param[in]   *pSrcA_s: Указатель на структуру первой матрицы
 * @param[in]   *pSrcB_s: Указатель на структуру второй матрицы
 * @param[out]  *pDst_s:  Указатель на структуру матрицы, в которую будет
 *                        записан результат сложения матриц
 *
 * @return  Статус операции
 *                @see ukfmo_fnc_status_e
 */
__UKFMO_ALWAYS_INLINE ukfmo_fnc_status_e
UKMO_MatrixAdition(
#if defined(__UKFMO_USE_ARM_MATH__)
	#if (__UKFMO_FPT_SIZE__)    == 4
		arm_matrix_instance_f32 *pSrcA_s,
		arm_matrix_instance_f32 *pSrcB_s,
		arm_matrix_instance_f32 *pDst_s
	#elif (__UKFMO_FPT_SIZE__)  == 8
		arm_matrix_instance_f64 *pSrcA_s,
		arm_matrix_instance_f64 *pSrcB_s,
		arm_matrix_instance_f64 *pDst_s
	#endif
#else
	ukfmo_matrix_s *pSrcA_s,
	ukfmo_matrix_s *pSrcB_s,
	ukfmo_matrix_s *pDst_s
#endif
)
{
	#if defined(__UKFMO_USE_ARM_MATH__)
	arm_status status_e;
	#if (__UKFMO_FPT_SIZE__) == 4
	status_e = arm_mat_add_f32(pSrcA_s, pSrcB_s, pDst_s);
	#else
	status_e = arm_mat_add_f64(pSrcA_s, pSrcB_s, pDst_s);
	#endif
	#else
	ukfmo_fnc_status_e status_e = UKFMO_OK;
	__UKFMO_FPT__ * const pDstL         = (__UKFMO_FPT__ *)pDst_s->pData;
	__UKFMO_FPT__ const * const pSrcA_  = (__UKFMO_FPT__ *)pSrcA_s->pData;
	__UKFMO_FPT__ const * const pSrcB_  = (__UKFMO_FPT__ *)pSrcB_s->pData;
	if ((pSrcA_s->columnNumb == pSrcB_s->columnNumb) && (pSrcA_s->rowNumb == pSrcB_s->rowNumb))
	{
		size_t eIdx;
		for (eIdx = 0; eIdx < pSrcA_s->columnNumb * pSrcA_s->rowNumb; eIdx++)
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

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      22-апр-2019
 *
 * @brief    Функция выполняет вычитание двух матриц
 *
 * @param[in]   *pSrcA_s: Указатель на структуру первой матрицы
 * @param[in]   *pSrcB_s: Указатель на структуру второй матрицы
 * @param[out]  *pDst_s:  Указатель на структуру матрицы, в которую будет
 *                        записан результат вычитания матриц
 *
 * @return  Статус операции
 *                 @see ukfmo_fnc_status_e
 *
 */
__UKFMO_ALWAYS_INLINE ukfmo_fnc_status_e
UKMO_MatrixSubstraction(
#if defined(__UKFMO_USE_ARM_MATH__)
	#if (__UKFMO_FPT_SIZE__)    == 4
		arm_matrix_instance_f32 *pSrcA_s,
		arm_matrix_instance_f32 *pSrcB_s,
		arm_matrix_instance_f32 *pDst_s
	#elif (__UKFMO_FPT_SIZE__)  == 8
		arm_matrix_instance_f64 *pSrcA_s,
		arm_matrix_instance_f64 *pSrcB_s,
		arm_matrix_instance_f64 *pDst_s
	#endif
#else
	ukfmo_matrix_s *pSrcA_s,
	ukfmo_matrix_s *pSrcB_s,
	ukfmo_matrix_s *pDst_s
#endif
)
{
	#if defined(__UKFMO_USE_ARM_MATH__)
	arm_status status_e;
	#if (__UKFMO_FPT_SIZE__) == 4
	status_e = arm_mat_sub_f32(pSrcA_s, pSrcB_s, pDst_s);
	#else
	status_e = arm_mat_sub_f64(pSrcA_s, pSrcB_s, pDst_s);
	#endif
	#else
	ukfmo_fnc_status_e status_e = UKFMO_OK;
	__UKFMO_FPT__ * const pDstL         = (__UKFMO_FPT__ *)pDst_s->pData;
	__UKFMO_FPT__ const * const pSrcA_  = (__UKFMO_FPT__ *)pSrcA_s->pData;
	__UKFMO_FPT__ const * const pSrcB_  = (__UKFMO_FPT__ *)pSrcB_s->pData;
	if ((pSrcA_s->columnNumb == pSrcB_s->columnNumb) && (pSrcA_s->rowNumb == pSrcB_s->rowNumb))
	{
		size_t eIdx;
		for (eIdx = 0; eIdx < pSrcA_s->columnNumb * pSrcA_s->rowNumb; eIdx++)
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

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      22-апр-2019
 *
 * @brief    Функция выполняет умножение двух матриц
 *
 * @param[in]   *pSrcA_s: Указатель на структуру первой матрицы
 * @param[in]   *pSrcB_s: Указатель на структуру второй матрицы
 * @param[out]  *pDst_s:  Указатель на структуру матрицы, в которую будет
 *                        записан результат умножения матриц
 *
 * @return  Статус операции
 *                 @see ukfmo_fnc_status_e
 *
 */
__UKFMO_ALWAYS_INLINE ukfmo_fnc_status_e
UKFMO_MatrixMultiplication(
#if defined(__UKFMO_USE_ARM_MATH__)
	#if (__UKFMO_FPT_SIZE__)    == 4
		arm_matrix_instance_f32 *pSrcA_s,
		arm_matrix_instance_f32 *pSrcB_s,
		arm_matrix_instance_f32 *pDst_s
	#elif (__UKFMO_FPT_SIZE__)  == 8
		arm_matrix_instance_f64 *pSrcA_s,
		arm_matrix_instance_f64 *pSrcB_s,
		arm_matrix_instance_f64 *pDst_s
	#endif
#else
	ukfmo_matrix_s *pSrcA_s,
	ukfmo_matrix_s *pSrcB_s,
	ukfmo_matrix_s *pDst_s
#endif
)
{
	#if defined(__UKFMO_USE_ARM_MATH__)
	arm_status status_e;
	#if (__UKFMO_FPT_SIZE__) == 4
	status_e = arm_mat_mult_f32(pSrcA_s, pSrcB_s, pDst_s);
	#else
	status_e = arm_mat_mult_f64(pSrcA_s, pSrcB_s, pDst_s);
	#endif
	#else
	ukfmo_fnc_status_e status_e = UKFMO_OK;
	__UKFMO_FPT__ const * const pSrc1L  = (__UKFMO_FPT__ *)pSrcA_s->pData;
	__UKFMO_FPT__ const * const pSrc2L  = (__UKFMO_FPT__ *)pSrcB_s->pData;
	__UKFMO_FPT__ * const pDstL         = (__UKFMO_FPT__ *)pDst_s->pData;
	size_t row, col, k;
	__UKFMO_FPT__ sum;

	if (pSrcA_s->columnNumb == pSrcB_s->rowNumb)
	{
		for (row = 0; row < pSrcA_s->rowNumb; row++)
		{
			for (col = 0; col < pSrcB_s->columnNumb; col++)
			{
				sum = 0;
				for (k = 0; k < pSrcA_s->columnNumb; k++)
				{
					sum += pSrc1L[pSrcA_s->columnNumb * row + k] * pSrc2L[pSrcB_s->columnNumb * k + col];
				}
				pDstL[pDst_s->columnNumb * row + col] = sum;
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
 * @brief    Функция выполняет умножение матрицы на скаляр
 *
 * @param[im]   *pSrc_s:  Указатель на структуру матрицы, которую необходимо
 *                        умножить на скаляр
 * @param[out]  *pDst_s:  Указатель на структуру матрицы, в которую будет
 *                        записан результат умножения матрицы на скаляр
 *
 * @return  Статус операции
 *                 @see ukfmo_fnc_status_e
 */
__UKFMO_ALWAYS_INLINE ukfmo_fnc_status_e
UKFMO_MatrixMultScale(
#if defined(__UKFMO_USE_ARM_MATH__)
	#if (__UKFMO_FPT_SIZE__)    == 4
		arm_matrix_instance_f32 *pSrc_s,
		__UKFMO_FPT__           scale,
		arm_matrix_instance_f32 *pDst_s
	#elif (__UKFMO_FPT_SIZE__)  == 8
		arm_matrix_instance_f64 *pSrc_s,
		__UKFMO_FPT__           scale,
		arm_matrix_instance_f64 *pDst_s
	#endif
#else
	ukfmo_matrix_s *pSrc_s,
	__UKFMO_FPT__   scale,
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

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      22-апр-2019
 *
 * @brief    Функция выполняет транспонирование матрицы
 *
 * @param[in]   *pSrc_s:  Указатель на структуру матрицы, транспонирование
 *                        которой необходимо выполнить
 * @param[out]  *pDst_s:  Указатель на структуру матрицы, в которую будет
 *                        записана транспонированная матрица
 *
 * @return  Статус операции
 *                 @see ukfmo_fnc_status_e
 */
__UKFMO_ALWAYS_INLINE ukfmo_fnc_status_e
UKFMO_MatrixTranspose(
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
	#if( __UKFMO_FPT_SIZE__) == 4
	status_e = arm_mat_trans_f32(pSrc_s, pDst_s);
	#else
	status_e = arm_mat_trans_f64(pSrc_s, pDst_s);
	#endif

	#else
	/* -->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
	__UKFMO_FPT__ const * const pSrcL   = (__UKFMO_FPT__ *)pSrc_s->pData;
	__UKFMO_FPT__ * const pDstL         = (__UKFMO_FPT__ *)pDst_s->pData;
	const uint16_t nRowSrcL = pSrc_s->rowNumb;
	const uint16_t nColSrcL = pSrc_s->columnNumb;
	const uint16_t nRowDstL = pDst_s->rowNumb;
	const uint16_t nColDstL = pDst_s->columnNumb;
	size_t row, col;

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

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      22-апр-2019
 *
 * @brief    Функция находит инверсную матрицу
 *
 * @param[in]   *pSrc_s:  Указатель на структуру матрицы от которой
 *                        необходимо найти инверсную матрицу
 * @param[out]  *pDst_s:  Указатель на структуру матрицы, в которую будет
 *                        записана инверсная матрица
 *
 * @return  Статус операции
 *                 @see ukfmo_fnc_status_e
 */
extern ukfmo_fnc_status_e
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
)__attribute__ ((section(".itcmram"))) ;


extern ukfmo_fnc_status_e
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
)__attribute__ ((section(".itcmram")));

extern ukfmo_fnc_status_e
UKFMO_MatrixInverse(
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
)__attribute__ ((section(".itcmram")));
/*#### |End  | <-- Секция - "Прототипы глобальных функций" ###################*/


/*#### |Begin| --> Секция - "Определение макросов" ###########################*/
/*#### |End  | <-- Секция - "Определение макросов" ###########################*/

#endif  /* LIB_A_UKFMO_UKF_MATRIX_OPERATIONS_H_ */

/*############################################################################*/
/*################################ END OF FILE ###############################*/
/*############################################################################*/
