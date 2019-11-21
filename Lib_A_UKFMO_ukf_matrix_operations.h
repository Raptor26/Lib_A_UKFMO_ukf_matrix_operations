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
#if defined (__UKFMO_EXTERN_MODE_ENABLE__)
	#include "macros_definitions.h"
#endif
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
		#define __UKFMO_INLINE              inline
	#endif

	/* static inline */
	#ifndef __UKFMO_STATIC_INLINE
		#define __UKFMO_STATIC_INLINE       static inline
	#endif

	/* always inline */
	#ifndef __UKFMO_ALWAYS_INLINE
		#define __UKFMO_ALWAYS_INLINE       inline __attribute__((always_inline)) static
	#endif

	/* force inline */
	#ifndef __UKFMO_FORCE_INLINE
		#define __UKFMO_FORCE_INLINE        inline __attribute__((always_inline))
	#endif

#else
	#define __UKFMO_INLINE
	#define __UKFMO_STATIC_INLINE   static
	#define __UKFMO_ALWAYS_INLINE
#endif

/*==== |Begin| --> Секция - Локальная оптимизация функций ====================*/
#if defined (__GNUC__)
	#ifndef __UKFMO_FNC_OPTIMIZE_MODE
		#define __UKFMO_FNC_OPTIMIZE_MODE
	#endif
#endif
/*==== |End| --> Секция - Локальная оптимизация функций ======================*/

/*==== |Begin| --> Секция - Расположение функций библиотеки в специальной
 *                          области памяти ===================================*/
#if defined (__UKFMO_FNC_MEMORY_LOCATION_NAME__)
	#if defined (__GNUC__)
		#define __UKFMO_FNC_MEMORY_LOCATION  __attribute__ ((section(__UKFMO_FNC_MEMORY_LOCATION_NAME__)))
	#else
		#error "You defined the name of the memory area for the function location, but the type of your compiler is not supported by the library. You can delete the macro definition __UKFMO_FNC_MEMORY_LOCATION_NAME__ or extend the macro definition __UKFMO_FNC_MEMORY_LOCATION for your compiler type"
	#endif
#else
	#define __UKFMO_FNC_MEMORY_LOCATION
#endif
/*==== |End  | <-- Секция - Расположение функций библиотеки в специальной
 *                          области памяти ===================================*/
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
	UKFMO_NOT_POS_DEFINED	 = -7,
	UKFMO_NOT_SQUARE		 = -8,
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
	uint16_t        numRows;
	uint16_t        numCols;
	__UKFMO_FPT__   *pData;
}
#if defined (__GNUC__)
	__attribute__((__packed__))
#else
	#error "Please, define compiler"
#endif
ukfmo_matrix_data_s;

#if defined(__UKFMO_USE_ARM_MATH__)
	#if (__UKFMO_FPT_SIZE__)    == 4
		#define ukfmo_matrix_s      arm_matrix_instance_f32
	#elif (__UKFMO_FPT_SIZE__)  == 8
		#define ukfmo_matrix_s      arm_matrix_instance_f64
	#endif
#else
	#define ukfmo_matrix_s      ukfmo_matrix_data_s
#endif
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
);

extern ukfmo_fnc_status_e
UKFMO_CopyParams(
#if defined(__UKFMO_USE_ARM_MATH__)
	#if (__UKFMO_FPT_SIZE__)    == 4
		arm_matrix_instance_f32 *pDst_s,
		arm_matrix_instance_f32 *pSrc_s
	#elif (__UKFMO_FPT_SIZE__)  == 8
		arm_matrix_instance_f64 *pDst_s,
		arm_matrix_instance_f64 *pSrc_s
	#endif
#else
	ukfmo_matrix_s *pDst_s,
	ukfmo_matrix_s *pSrc_s
#endif
);

extern ukfmo_fnc_status_e __UKFMO_FNC_OPTIMIZE_MODE
UKFMO_CopyMatrix(
#if defined(__UKFMO_USE_ARM_MATH__)
	#if (__UKFMO_FPT_SIZE__) 	== 4
		arm_matrix_instance_f32 *pDst_s,
		arm_matrix_instance_f32 *pSrc_s
	#elif (__UKFMO_FPT_SIZE__) 	== 8
		arm_matrix_instance_f64 *pDst_s,
		arm_matrix_instance_f64 *pSrc_s
	#endif
#else
	ukfmo_matrix_s *pDst_s,
	ukfmo_matrix_s *pSrc_s
#endif
) __UKFMO_FNC_MEMORY_LOCATION;

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
);

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
);

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
);

extern ukfmo_fnc_status_e __UKFMO_FNC_OPTIMIZE_MODE
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
) __UKFMO_FNC_MEMORY_LOCATION;

extern ukfmo_fnc_status_e __UKFMO_FNC_OPTIMIZE_MODE
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
) __UKFMO_FNC_MEMORY_LOCATION;

extern ukfmo_fnc_status_e __UKFMO_FNC_OPTIMIZE_MODE
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
) __UKFMO_FNC_MEMORY_LOCATION;

extern ukfmo_fnc_status_e __UKFMO_FNC_OPTIMIZE_MODE
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
) __UKFMO_FNC_MEMORY_LOCATION;

extern ukfmo_fnc_status_e __UKFMO_FNC_OPTIMIZE_MODE
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
) __UKFMO_FNC_MEMORY_LOCATION;

extern ukfmo_fnc_status_e __UKFMO_FNC_OPTIMIZE_MODE
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
) __UKFMO_FNC_MEMORY_LOCATION;

extern ukfmo_fnc_status_e __UKFMO_FNC_OPTIMIZE_MODE
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
) __UKFMO_FNC_MEMORY_LOCATION;
/*#### |End  | <-- Секция - "Прототипы глобальных функций" ###################*/


/*#### |Begin| --> Секция - "Определение макросов" ###########################*/

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      22-авг-2019
 *
 * @brief Если макрос __UKFMO_ALL_INTERRUPT_DIS() объявлен, то
 *        используется его внешнее определение, иначе используется заглушка
 *        @note Макрос должен отключать прерывния в системе, чтобы ОС не могла
 *        		переключать задачи
 *
 * @return 	None
 */
#if defined (__UKFMO_ALL_INTERRUPTS_DIS)
#else
	#define __UKFMO_ALL_INTERRUPTS_DIS()
#endif

#if defined (__UKFMO_CHEKING_ENABLE__)
/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      22-авг-2019
 *
 * @brief    Макрос для проверки валидности структуры матрицы
 *
 * @param[in] x: Указатель на структуру матрицы
 * @param[in] rowMaw: Максимальное количество строк матрицы
 * @param[in] colMax: Максимальное количество столбцов матрицы
 *
 * @return 	Возвращает 1u если параметры структуры валидны, иначе 0u
 */
#define __UKFMO_IsMatrixStructValid(x, rowMaw, colMax) \
	(((((x)->numRows != 0u) && ((x)->numRows <= (rowMaw))) && \
	(  ((x)->numCols != 0u) && ((x)->numCols <= (rowMaw))) && \
	(   (x)->pData != NULL)) == 1u)
#else
#define __UKFMO_IsMatrixStructValid(x, rowMax, colMax) (1u)
#endif

#if defined (__UKFMO_CHEKING_ENABLE__)
/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      22-авг-2019
 *
 * @brief    Макрос зацикливает программу в случае неверных параметров
 *           структуры матрицы
 *
 * @param[in] x: Указатель на структуру матрицы
 * @param[in] rowMaw: Максимальное количество строк матрицы
 * @param[in] colMax: Максимальное количество столбцов матрицы
 *
 * @return None
 */
#define __UKFMO_CheckMatrixStructValidationGeneric(x, rowMaw, colMax) \
	if (__UKFMO_IsMatrixStructValid((x), (rowMaw), (colMax)) != 1u) { __UKFMO_ALL_INTERRUPTS_DIS(); while(1);}


#if !defined (__UKFMO_CheckMatrixStructValidation)

	/*-------------------------------------------------------------------------*//**
	* @author    Mickle Isaev
	* @date      22-авг-2019
	*
	* @brief    Макрос зацикливает программу в случае неверных параметров
	*           структуры матрицы
	*
	* @param[in] 	x: 	Указатель на структуру матрицы
	*
	* @return None
	*/
	#define __UKFMO_CheckMatrixStructValidation(x) __UKFMO_CheckMatrixStructValidationGeneric((x), (UINT16_MAX), (UINT16_MAX))
#endif

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      09-сен-2019
 *
 * @brief    Макрос выполняет проверку на совпадение адресов памяти двух матриц
 *
 * @param[in]   mat1: 	Указатель на область памяти матрицы 1
 * @param[in] 	mat2:   Указатель на область памяти матрицы 2
 *
 * @return  	возвращает 1, если адреса различаются
 */
#define __UKFMO_IsMatAddrDiff(mat1, mat2)	\
	((mat1->pData != mat2->pData) == 1u)

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      09-сен-2019
 *
 * @brief     Макрос зацикливает программу в случае совпадения областей памяти
 *            в которых хранятся матрицы
 *
 * @param    mat1    Матрица 1
 * @param    mat2    Матрица 2
 *
 * @return   None
 */
#define __UKFMO_CheckMatAddrDiff(mat1, mat2) \
	if(__UKFMO_IsMatAddrDiff((mat1), (mat2)) != 1u) {__UKFMO_ALL_INTERRUPTS_DIS(); while(1);}

#else
#define __UKFMO_CheckMatrixStructValidationGeneric(x, rowMaw, colMax)

#if defined (__UKFMO_CheckMatrixStructValidation)
	#error "Delete define __UKFMO_CheckMatrixStructValidation() in macros_definition.h"
#else
	#define __UKFMO_CheckMatrixStructValidation(x) __UKFMO_CheckMatrixStructValidationGeneric((x), (UINT16_MAX), (UINT16_MAX))
#endif

#define __UKFMO_IsMatAddrDiff(mat1, mat2)
#define __UKFMO_CheckMatAddrDiff(mat1, mat2);
#endif

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      04-сен-2019
 *
 * @brief    Макрос возвращает количество строк матрицы
 *
 * @param[in] 	*pMatrix_s: Указатель на матрицу
 *
 * @return Количество строк матрицы
 */
#define __UKFMO_GetRowNumb(pMatrix_s) 		((pMatrix_s)->numRows)

/*-------------------------------------------------------------------------*//**
* @author    Mickle Isaev
* @date      04-сен-2019
*
* @brief    Макрос возвращает количество столбцов матрицы
*
* @param[in] 	*pMatrix_s: Указатель на матрицу
*
* @return Количество столбцов матрицы
*/
#define __UKFMO_GetColNumb(pMatrix_s) 		((pMatrix_s)->numCols)

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      04-сен-2019
 *
 * @brief    Маакрос возвращает количество ячеек матрицы
 *
 * @param[in] 	*pMatrix_s: Указатель на структуру матрицы
 *
 * @return Общее количество ячеек матрицы
 */
#define __UKFMO_GetCellNumb(pMatrix_s) 		(__UKFMO_GetRowNumb(pMatrix_s) * __UKFMO_GetColNumb(pMatrix_s))

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      04-сен-2019
 *
 * @brief    Макрос приводит заданную позицию ячейки из двумерного массива
 *           к одномерному
 *
 * @param[in] 	*pMatrix_s: Указатель на структуру матрицы
 * @param[in]   rowPos: 	Заданная строка матрицы
 * @param[in]   colPos:    	Заданный столбец матрицы
 *
 * @return  Номер ячейки для одномерного массива, которая будет соответствовать
 *          заданной позиции
 */
#define __UKFMO_GetIndexInOneFromTwoDim(pMatrix_s, rowPos, colPos) \
	(__UKFMO_GetColNumb(pMatrix_s) * (rowPos) + (colPos))

#if defined (__UKFMO_CHEKING_ENABLE__)
/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      04-сен-2019
 *
 * @brief    Макрос проверяет размер матрицы с размером массива, в котором
 *           эта матрица хранится.
 *           Если размеры не совпадают, то программа зацикливается
 *
 * @param[in] 	*pMatrix_s: Указатель на структуру матрицы
 * @param[in] 	sizeofArr: 	Результат оператора sizeof (размер массива в байтах)
 *
 * @return   None
 */
#define __UKFMO_CheckMatrixSize(pMatrix_s, sizeofArr) \
	while ((__UKFMO_GetCellNumb((pMatrix_s)) * sizeof(__UKFMO_FPT__)) != (sizeofArr)) {__UKFMO_ALL_INTERRUPTS_DIS();}

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      09-сен-2019
 *
 * @brief    Макрос выполняет проверку статуса матричной операции, в случае
 *           неудачи, зацикливает программу.
 * @warninng 		Макрос не зацикливает программу, если обнаружены
 *             		следующие ошибки:
 *             		- UKFMO_SINGULAR
 *             		- UKFMO_NOT_POS_DEFINED
 *
 * @param[in] 	status: Статус матричной операции
 * 						@see ukfmo_fnc_status_e
 *
 * @return   None
 */
#define __UKFMO_CheckMatrixOperationStatus(status) \
	if(status != UKFMO_OK) \
	{\
		if(status == UKFMO_SINGULAR) \
		{} \
		else if(status == UKFMO_NOT_POS_DEFINED)\
		{} \
		else\
		{ \
			__UKFMO_ALL_INTERRUPTS_DIS(); while(1);\
		} \
	}

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      09-сен-2019
 *
 * @brief    Макрос зацикливает программу, если обнаружена ошибка
 *           сингулярности матрицы
 *
 * @param[in] 	status: Статус матричной операции
 * 						@see ukfmo_fnc_status_e
 *
 * @return   None
 */
#define __UKFMO_CheckMatrixSingularity(status)		\
	if((status == UKFMO_SINGULAR)) {__UKFMO_ALL_INTERRUPTS_DIS(); while(1);}

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      09-сен-2019
 *
 * @brief    Макрос зацикливает программу, если обнаружена
 *           ошибка "UKFMO_NOT_POS_DEFINED"
 *
 * @param[in] 	status: Статус матричной операции
 * 						@see ukfmo_fnc_status_e
 *
 * @return   None
 */
#define __UKFMO_CheckMatrixPosDefine(status) \
	if((status == UKFMO_NOT_POS_DEFINED)) {__UKFMO_ALL_INTERRUPTS_DIS(); while(1);}
#else

#define __UKFMO_CheckMatrixSize(pMatrix_s, sizeofArr)
#define __UKFMO_CheckMatrixOperationStatus(status)
#define __UKFMO_CheckMatrixSingularity(status)
#define __UKFMO_CheckMatrixPosDefine(status)
#endif

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      21-ноя-2019
 *
 * @brief   Макрос выполняет инициализацию двумерной матрицы и проверяет
 * 			размерность матрицы на размерность выделенной под эту матрицу области
 * 			памяти.
 * 			@warning 	Макрос войдет в бесконечный цикл если количество строк и
 * 						столбцов не совпадает с размерностью области памяти, которая
 * 						выделена под эту матрицу. Т.е. Если (rowNumb * colNumb != sizeof(pMem_a2) / sizeof(pMem_a2[0][0]))
 *
 * @param[out] 	pMat_s:  	Указатель на структуру матрицы
 * @param[in]   rowNumb:    Количество строк матрицы
 * @param[in]   colNumb:    Количество столбцов матрицы
 * @param[in]   pMem_a2:   	Область памяти, в которой будут расположены
 * 							ячейки матрицы
 * @return None
 *
 * {@code
 * 		int main (void)
 * 		{
 * 			double memForMatrix_a2[3][7];
 * 			ukfmo_matrix_s matrix_s;
 * 			__UKFMO_MatrixInit(
 * 				(&matrix_s), 		// Указатель на структуру матрицы (необходимо использовать скобки)
 * 				3u, 				// Количество строк
 * 				7u, 				// Количество столбцов
 *
 * 				memForMatrix_a2);	// Указатель на начало двумерного массива, в котором
 * 									// будут расположены ячейки матрицы.
 * 									// @note указатель на двумерный массив нужно передавать как в примере, иначе
 * 									// проверка на размерность с помощью оператора sizeof не будет пройдена.
 * 									// @warning не нужно использовать &memForMatrix_a2[0][0].
 * 		}
 *
 * }
 */
#define __UKFMO_MatrixInit(pMat_s, rowNumb, colNumb, pMem_a2)		\
do{																	\
	ukfmo_matrix_s *pMatTmp_s = (pMat_s);							\
	pMatTmp_s->numCols 	= (colNumb);								\
	pMatTmp_s->numRows 	= (rowNumb);								\
	pMatTmp_s->pData 	= (__UKFMO_FPT__*) pMem_a2;					\
	if(__UKFMO_GetCellNumb(pMatTmp_s) != 							\
		(sizeof(pMem_a2) / sizeof(pMem_a2[0u][0u])))				\
	{																\
		__UKFMO_ALL_INTERRUPTS_DIS();								\
		while(1);													\
	}																\
}while(0u)															\
/*#### |End  | <-- Секция - "Определение макросов" ###########################*/

#endif  /* LIB_A_UKFMO_UKF_MATRIX_OPERATIONS_H_ */

/*############################################################################*/
/*################################ END OF FILE ###############################*/
/*############################################################################*/
