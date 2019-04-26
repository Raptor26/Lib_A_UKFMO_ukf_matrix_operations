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
#include "Lib_A_UKFMO_macros_definitions.h"
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

#if defined (__GNUC__)
	#ifndef __UKFMO_OPTIMIZE_O0
		#define __UKFMO_OPTIMIZE_O0         __attribute__((optimize("O0")))
	#endif

	#ifndef __UKFMO_OPTIMIZE_O1
		#define __UKFMO_OPTIMIZE_O1         __attribute__((optimize("O1")))
	#endif

	#ifndef __UKFMO_OPTIMIZE_O2
		#define __UKFMO_OPTIMIZE_O2         __attribute__((optimize("O2")))
	#endif

	#ifndef __UKFMO_OPTIMIZE_O3
		#define __UKFMO_OPTIMIZE_O3         __attribute__((optimize("O3")))
	#endif

	#ifndef __UKFMO_OPTIMIZE_OFAST
		#define __UKFMO_OPTIMIZE_OFAST      __attribute__((optimize("Ofast")))
	#endif

	#ifndef __UKFMO_OPTIMIZE_OS
		#define __UKFMO_OPTIMIZE_OS         __attribute__((optimize("Os")))
	#endif

#else
	#ifndef __UKFMO_OPTIMIZE_O0
		#define __UKFMO_OPTIMIZE_O0
	#endif

	#ifndef __UKFMO_OPTIMIZE_O1
		#define __UKFMO_OPTIMIZE_O1
	#endif

	#ifndef __UKFMO_OPTIMIZE_O2
		#define __UKFMO_OPTIMIZE_O2
	#endif

	#ifndef __UKFMO_OPTIMIZE_O3
		#define __UKFMO_OPTIMIZE_O3
	#endif

	#ifndef __UKFMO_OPTIMIZE_OFAST
		#define __UKFMO_OPTIMIZE_OFAST
	#endif

	#ifndef __UKFMO_OPTIMIZE_OS
		#define __UKFMO_OPTIMIZE_OS
	#endif
#endif

#if defined (__UKFMO_FNC_SPACE_NAME)
	#if defined (__GNUC__)
		#define __UKFMO_FNC_LOCATION_IN_SPECIAL_SPACE  __attribute__ ((section(__UKFMO_FNC_SPACE_NAME)))
	#else
		#error "You defined the name of the memory area for the function location, but the type of your compiler is not supported by the library. You can delete the macro definition __UKFMO_FNC_SPACE_NAME or extend the macro definition __UKFMO_LOCATION_IN_SPECIAL_SPACE for your compiler type"
	#endif
#else
	#define __UKFMO_FNC_LOCATION_IN_SPECIAL_SPACE
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

extern ukfmo_fnc_status_e __UKFMO_OPTIMIZE_OFAST
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
) __UKFMO_FNC_LOCATION_IN_SPECIAL_SPACE;

extern ukfmo_fnc_status_e __UKFMO_OPTIMIZE_OFAST
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
) __UKFMO_FNC_LOCATION_IN_SPECIAL_SPACE;

extern ukfmo_fnc_status_e __UKFMO_OPTIMIZE_OFAST
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
) __UKFMO_FNC_LOCATION_IN_SPECIAL_SPACE;

extern ukfmo_fnc_status_e __UKFMO_OPTIMIZE_OFAST
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
) __UKFMO_FNC_LOCATION_IN_SPECIAL_SPACE;

extern ukfmo_fnc_status_e __UKFMO_OPTIMIZE_OFAST
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
) __UKFMO_FNC_LOCATION_IN_SPECIAL_SPACE;

extern ukfmo_fnc_status_e __UKFMO_OPTIMIZE_OFAST
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
) __UKFMO_FNC_LOCATION_IN_SPECIAL_SPACE;

extern ukfmo_fnc_status_e __UKFMO_OPTIMIZE_OFAST
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
) __UKFMO_FNC_LOCATION_IN_SPECIAL_SPACE;
/*#### |End  | <-- Секция - "Прототипы глобальных функций" ###################*/


/*#### |Begin| --> Секция - "Определение макросов" ###########################*/
/*#### |End  | <-- Секция - "Определение макросов" ###########################*/

#endif  /* LIB_A_UKFMO_UKF_MATRIX_OPERATIONS_H_ */

/*############################################################################*/
/*################################ END OF FILE ###############################*/
/*############################################################################*/
