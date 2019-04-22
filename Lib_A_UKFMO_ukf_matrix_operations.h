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
	UKFMO_OK                = ARM_MATH_SUCCESS,
	UKFMO_ARGUMENT_ERROR    = ARM_MATH_ARGUMENT_ERROR,
	UKFMO__LENGTH_ERROR     = ARM_MATH_LENGTH_ERROR,
	UKFMO_SIZE_MISMATCH     = ARM_MATH_SIZE_MISMATCH,
	UKFMO_NANINF            = ARM_MATH_NANINF,
	UKFMO_SINGULAR          = ARM_MATH_SINGULAR,
	UKFMO_TEST_FAULURE      = ARM_MATH_TEST_FAILURE,
	#else
	UKFMO_OK = 0,
	UKFMO_ERROR,
	UKFMO_SIZE_MISMATCH,
	UKFMO_SINGULAR,
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
/*#### |End  | <-- Секция - "Прототипы глобальных функций" ###################*/


/*#### |Begin| --> Секция - "Определение макросов" ###########################*/
/*#### |End  | <-- Секция - "Определение макросов" ###########################*/

#endif  /* LIB_A_UKFMO_UKF_MATRIX_OPERATIONS_H_ */

/*############################################################################*/
/*################################ END OF FILE ###############################*/
/*############################################################################*/
