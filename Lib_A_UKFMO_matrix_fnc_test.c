/**
 * @file   	%<%NAME%>%.%<%EXTENSION%>%
 * @author 	%<%USER%>%
 * @version
 * @date 	%<%DATE%>%, %<%TIME%>%
 * @brief
 */


/*#### |Begin| --> Секция - "Include" ########################################*/
#include "Lib_A_UKFMO_matrix_fnc_test.h"
/*#### |End  | <-- Секция - "Include" ########################################*/
#if defined (__UKFMOTEST_ENABLE__)
#define UKFMOTEST_MATRIX_ROW				7u
#define UKFMOTEST_MATRIX_COLUMN				7u
#if defined(__UKFMO_USE_ARM_MATH__)
	#if (__UKFMO_FPT_SIZE__)    == 4
		#define UKFMOTEST_MATRIX_S arm_matrix_instance_f32
	#else
		#define UKFMOTEST_MATRIX_S arm_matrix_instance_f64
	#endif
#else
	#define UKFMOTEST_MATRIX_S ukfmo_matrix_s
#endif
/*#### |Begin| --> Секция - "Глобальные переменные" ##########################*/
__UKFMO_FPT__ UKFMOTEST_initialMatrix_a[UKFMOTEST_MATRIX_ROW][UKFMOTEST_MATRIX_COLUMN] __attribute__ ((section("._user_heap_stack")));
UKFMOTEST_MATRIX_S UKFMOTEST_initialMatrix_s __attribute__ ((section("._user_heap_stack")));

__UKFMO_FPT__ UKFMOTEST_matrixA_a[UKFMOTEST_MATRIX_ROW][UKFMOTEST_MATRIX_COLUMN] __attribute__ ((section("._user_heap_stack")));
UKFMOTEST_MATRIX_S UKFMOTEST_matrixA_s __attribute__ ((section("._user_heap_stack")));

__UKFMO_FPT__ UKFMOTEST_matrixB_a[UKFMOTEST_MATRIX_ROW][UKFMOTEST_MATRIX_COLUMN];
UKFMOTEST_MATRIX_S UKFMOTEST_matrixB_s __attribute__ ((section("._user_heap_stack")));

__UKFMO_FPT__ UKFMOTEST_matrixC_a[UKFMOTEST_MATRIX_ROW][UKFMOTEST_MATRIX_COLUMN] __attribute__ ((section("._user_heap_stack")));
UKFMOTEST_MATRIX_S UKFMOTEST_matrixC_s __attribute__ ((section("._user_heap_stack")));


//__UKFMO_FPT__ UKFMOTEST_initialMatrix_a[UKFMOTEST_MATRIX_ROW][UKFMOTEST_MATRIX_COLUMN];
//UKFMOTEST_MATRIX_S UKFMOTEST_initialMatrix_s;
//
//__UKFMO_FPT__ UKFMOTEST_matrixA_a[UKFMOTEST_MATRIX_ROW][UKFMOTEST_MATRIX_COLUMN];
//UKFMOTEST_MATRIX_S UKFMOTEST_matrixA_s;
//
//__UKFMO_FPT__ UKFMOTEST_matrixB_a[UKFMOTEST_MATRIX_ROW][UKFMOTEST_MATRIX_COLUMN];
//UKFMOTEST_MATRIX_S UKFMOTEST_matrixB_s;
//
//__UKFMO_FPT__ UKFMOTEST_matrixC_a[UKFMOTEST_MATRIX_ROW][UKFMOTEST_MATRIX_COLUMN];
//UKFMOTEST_MATRIX_S UKFMOTEST_matrixC_s;


__UKFMO_FPT__ UKFMOTEST_matrixAddition_a2[UKFMOTEST_MATRIX_ROW][UKFMOTEST_MATRIX_COLUMN] __attribute__ ((section("._user_heap_stack")));
UKFMOTEST_MATRIX_S UKFMOTEST_matrixAddition_s __attribute__ ((section("._user_heap_stack")));
uint32_t UKFMOTEST_matrixAdditionRunTime;

__UKFMO_FPT__ UKFMOTEST_matrixSub_a2[UKFMOTEST_MATRIX_ROW][UKFMOTEST_MATRIX_COLUMN] __attribute__ ((section("._user_heap_stack")));
UKFMOTEST_MATRIX_S UKFMOTEST_matrixSub_s __attribute__ ((section("._user_heap_stack")));
uint32_t UKFMOTEST_matrixSubRunTime;

__UKFMO_FPT__ UKFMOTEST_matrixMult_a2[UKFMOTEST_MATRIX_ROW][UKFMOTEST_MATRIX_COLUMN] __attribute__ ((section("._user_heap_stack")));
UKFMOTEST_MATRIX_S UKFMOTEST_matrixMult_s __attribute__ ((section("._user_heap_stack")));
uint32_t UKFMOTEST_matrixMultRunTime;

__UKFMO_FPT__ UKFMOTEST_matrixMultScale_a2[UKFMOTEST_MATRIX_ROW][UKFMOTEST_MATRIX_COLUMN] __attribute__ ((section("._user_heap_stack")));
UKFMOTEST_MATRIX_S UKFMOTEST_matrixMultScale_s __attribute__ ((section("._user_heap_stack")));
uint32_t UKFMOTEST_matrixMultScaleRunTime;

__UKFMO_FPT__ UKFMOTEST_matrixTranspose_a2[UKFMOTEST_MATRIX_ROW][UKFMOTEST_MATRIX_COLUMN] __attribute__ ((section("._user_heap_stack")));
UKFMOTEST_MATRIX_S UKFMOTEST_matrixTranspose_s __attribute__ ((section("._user_heap_stack")));
uint32_t UKFMOTEST_matrixTransposeRunTime;

__UKFMO_FPT__ UKFMOTEST_matrixInv_a2[UKFMOTEST_MATRIX_ROW][UKFMOTEST_MATRIX_COLUMN] __attribute__ ((section("._user_heap_stack")));
UKFMOTEST_MATRIX_S UKFMOTEST_matrixInv_s __attribute__ ((section("._user_heap_stack")));
uint32_t UKFMOTEST_matrixInvRunTime;

__UKFMO_FPT__ UKFMOTEST_matrixCholLow_a2[UKFMOTEST_MATRIX_ROW][UKFMOTEST_MATRIX_COLUMN] __attribute__ ((section("._user_heap_stack")));
UKFMOTEST_MATRIX_S UKFMOTEST_matrixCholLow_s __attribute__ ((section("._user_heap_stack")));
uint32_t UKFMOTEST_matrixCholLowRunTime;

vtrm_tmr_s UKFMOTEST_vTMR_s ;

uint32_t UKFMOTEST_choleskyRunTime;
uint32_t UKFMOTEST_InverseRunTime;
#endif
/*#### |End  | <-- Секция - "Глобальные переменные" ##########################*/


/*#### |Begin| --> Секция - "Локальные переменные" ###########################*/
/*#### |End  | <-- Секция - "Локальные переменные" ###########################*/


/*#### |Begin| --> Секция - "Прототипы локальных функций" ####################*/
/*#### |End  | <-- Секция - "Прототипы локальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание глобальных функций" ####################*/
void
UKFMOTEST_Test(void)
{
#if defined (__UKFMOTEST_ENABLE__)
	vtrm_tmr_init_s tmrInit_s;
	VTMR_StructInit(&tmrInit_s);
	tmrInit_s.pHighCntReg = HC32_UPPER_CNT_FOR_VTMR;
	tmrInit_s.pLowCntReg = HC32_LOWER_CNT_FOR_VTMR;
	VTMR_Init(&UKFMOTEST_vTMR_s, &tmrInit_s);

//	VTMR_StartTimer(&UKFMOTEST_vTMR_s);

	UKFMO_MatrixInit(
		&UKFMOTEST_initialMatrix_s,
		UKFMOTEST_MATRIX_ROW,
		UKFMOTEST_MATRIX_COLUMN,
		(__UKFMO_FPT__*) UKFMOTEST_initialMatrix_a);



	/* step1 */
	UKFMO_MatrixZeros(&UKFMOTEST_initialMatrix_s);

	/* step2 */
	UKFMO_MatrixIdentity(&UKFMOTEST_initialMatrix_s);

	/* step 3*/
	UKFMO_MatrixMultScale(
		&UKFMOTEST_initialMatrix_s,
		(__UKFMO_FPT__)0.33,
		&UKFMOTEST_initialMatrix_s);

	/* step4 */
	UKFMO_MatrixInit(
			&UKFMOTEST_matrixA_s,
			UKFMOTEST_MATRIX_ROW,
			UKFMOTEST_MATRIX_COLUMN,
			(__UKFMO_FPT__*) UKFMOTEST_matrixA_a);
	UKFMOTEST_matrixA_a[0][0] = 0.55;
	UKFMOTEST_matrixA_a[0][1] = 0.65;
	UKFMOTEST_matrixA_a[0][2] = 0.75;
	UKFMOTEST_matrixA_a[0][3] = 0.85;
	UKFMOTEST_matrixA_a[0][4] = 0.95;

	UKFMOTEST_matrixA_a[1][0] = -0.55;
	UKFMOTEST_matrixA_a[1][1] = -0.65;
	UKFMOTEST_matrixA_a[1][2] = -0.75;
	UKFMOTEST_matrixA_a[1][3] = -0.85;
	UKFMOTEST_matrixA_a[1][4] = -0.95;

	UKFMOTEST_matrixA_a[4][0] += 0.55;
	UKFMOTEST_matrixA_a[3][1] += 0.65;
	UKFMOTEST_matrixA_a[2][2] += 0.75;
	UKFMOTEST_matrixA_a[1][3] += 0.85;
	UKFMOTEST_matrixA_a[0][4] += 0.95;

	/* step5 */
	UKFMO_MatrixMultiplication(
		&UKFMOTEST_initialMatrix_s,
		&UKFMOTEST_matrixA_s,
		&UKFMOTEST_matrixA_s);

	/* step6 */
	UKFMO_MatrixTranspose(
		&UKFMOTEST_matrixA_s,
		&UKFMOTEST_initialMatrix_s);

	/* step7 */

	UKFMO_MatrixInit(
			&UKFMOTEST_matrixB_s,
			UKFMOTEST_MATRIX_ROW,
			UKFMOTEST_MATRIX_COLUMN,
			(__UKFMO_FPT__*) UKFMOTEST_matrixB_a);

	UKFMO_MatrixMultiplication(
		&UKFMOTEST_initialMatrix_s,
		&UKFMOTEST_matrixA_s,
		&UKFMOTEST_matrixB_s);

	/* step8 */
	UKFMO_MatrixInit(
				&UKFMOTEST_matrixC_s,
				UKFMOTEST_MATRIX_ROW,
				UKFMOTEST_MATRIX_COLUMN,
				(__UKFMO_FPT__*) UKFMOTEST_matrixC_a);
	UKFMO_MatrixZeros(&UKFMOTEST_matrixC_s);
	UKFMOTEST_matrixC_a[0][0] = 0.514428619342896;
	UKFMOTEST_matrixC_a[1][1] = 0.514428619342896;
	UKFMOTEST_matrixC_a[2][2] = 0.514428619342896;
	UKFMOTEST_matrixC_a[3][3] = 0.514428619342896;
	UKFMOTEST_matrixC_a[4][4] = 0.514428619342896;
	UKFMOTEST_matrixC_a[5][5] = 0.514428619342896;
	UKFMOTEST_matrixC_a[6][6] = 0.514428619342896;

	/* step9 */
	VTMR_StartTimer(&UKFMOTEST_vTMR_s);
	UKFMO_MatrixInverse(
		&UKFMOTEST_matrixC_s,
		&UKFMOTEST_matrixB_s);
	UKFMOTEST_InverseRunTime =
		VTMR_GetTimerValue(&UKFMOTEST_vTMR_s);

	VTMR_StartTimer(&UKFMOTEST_vTMR_s);
	UKFMO_GetCholeskyLow(&UKFMOTEST_matrixB_s);
	UKFMOTEST_choleskyRunTime =
		VTMR_GetTimerValue(&UKFMOTEST_vTMR_s);

	/* step10 */
//	UKMO_MatrixSubstraction(
//		&UKFMOTEST_matrixB_s,
//		&UKFMOTEST_initialMatrix_s,
//		&UKFMOTEST_initialMatrix_s);
#endif
}

void
UKFMOTEST_Test7x7(void)
{
#if defined (__UKFMOTEST_ENABLE__)
	vtrm_tmr_init_s tmrInit_s;
		VTMR_StructInit(&tmrInit_s);
		tmrInit_s.pHighCntReg = HC32_UPPER_CNT_FOR_VTMR;
		tmrInit_s.pLowCntReg = HC32_LOWER_CNT_FOR_VTMR;
		VTMR_Init(&UKFMOTEST_vTMR_s, &tmrInit_s);

	/* Инициализация всех матриц */
	UKFMO_MatrixInit(
		&UKFMOTEST_matrixAddition_s,
		UKFMOTEST_MATRIX_ROW,
		UKFMOTEST_MATRIX_COLUMN,
		(__UKFMO_FPT__*) UKFMOTEST_matrixAddition_a2);

	UKFMO_MatrixInit(
		&UKFMOTEST_matrixSub_s,
		UKFMOTEST_MATRIX_ROW,
		UKFMOTEST_MATRIX_COLUMN,
		(__UKFMO_FPT__*) UKFMOTEST_matrixSub_a2);

	UKFMO_MatrixInit(
		&UKFMOTEST_matrixMult_s,
		UKFMOTEST_MATRIX_ROW,
		UKFMOTEST_MATRIX_COLUMN,
		(__UKFMO_FPT__*) UKFMOTEST_matrixMult_a2);

	UKFMO_MatrixInit(
		&UKFMOTEST_matrixMultScale_s,
		UKFMOTEST_MATRIX_ROW,
		UKFMOTEST_MATRIX_COLUMN,
		(__UKFMO_FPT__*) UKFMOTEST_matrixMultScale_a2);

	UKFMO_MatrixInit(
		&UKFMOTEST_matrixTranspose_s,
		UKFMOTEST_MATRIX_ROW,
		UKFMOTEST_MATRIX_COLUMN,
		(__UKFMO_FPT__*) UKFMOTEST_matrixTranspose_a2);

	UKFMO_MatrixInit(
		&UKFMOTEST_matrixInv_s,
		UKFMOTEST_MATRIX_ROW,
		UKFMOTEST_MATRIX_COLUMN,
		(__UKFMO_FPT__*) UKFMOTEST_matrixInv_a2);

	UKFMO_MatrixInit(
		&UKFMOTEST_matrixCholLow_s,
		UKFMOTEST_MATRIX_ROW,
		UKFMOTEST_MATRIX_COLUMN,
		(__UKFMO_FPT__*) UKFMOTEST_matrixCholLow_a2);

	/* Замер времени выполнения */
	VTMR_StartTimer(&UKFMOTEST_vTMR_s);
	UKFMO_GetCholeskyLow(&UKFMOTEST_matrixCholLow_s);
	UKFMOTEST_matrixCholLowRunTime =
		VTMR_GetTimerValue(&UKFMOTEST_vTMR_s);

	VTMR_StartTimer(&UKFMOTEST_vTMR_s);
	UKFMO_MatrixInverse(&UKFMOTEST_matrixCholLow_s, &UKFMOTEST_matrixInv_s);
	UKFMOTEST_matrixInvRunTime =
		VTMR_GetTimerValue(&UKFMOTEST_vTMR_s);

	VTMR_StartTimer(&UKFMOTEST_vTMR_s);
	UKFMO_MatrixTranspose(&UKFMOTEST_matrixInv_s, &UKFMOTEST_matrixTranspose_s);
	UKFMOTEST_matrixTransposeRunTime =
		VTMR_GetTimerValue(&UKFMOTEST_vTMR_s);

	VTMR_StartTimer(&UKFMOTEST_vTMR_s);
	UKFMO_MatrixMultScale(&UKFMOTEST_matrixTranspose_s, (__UKFMO_FPT__) 0.5, &UKFMOTEST_matrixMultScale_s);
	UKFMOTEST_matrixMultScaleRunTime =
		VTMR_GetTimerValue(&UKFMOTEST_vTMR_s);

	VTMR_StartTimer(&UKFMOTEST_vTMR_s);
	UKFMO_MatrixMultiplication(&UKFMOTEST_matrixTranspose_s, &UKFMOTEST_matrixMultScale_s, &UKFMOTEST_matrixMult_s);
	UKFMOTEST_matrixMultRunTime =
		VTMR_GetTimerValue(&UKFMOTEST_vTMR_s);

	VTMR_StartTimer(&UKFMOTEST_vTMR_s);
	UKMO_MatrixSubstraction(&UKFMOTEST_matrixTranspose_s, &UKFMOTEST_matrixMult_s, &UKFMOTEST_matrixSub_s);
	UKFMOTEST_matrixSubRunTime =
		VTMR_GetTimerValue(&UKFMOTEST_vTMR_s);

	VTMR_StartTimer(&UKFMOTEST_vTMR_s);
	UKMO_MatrixAdition(&UKFMOTEST_matrixTranspose_s, &UKFMOTEST_matrixMult_s, &UKFMOTEST_matrixAddition_s);
	UKFMOTEST_matrixAdditionRunTime =
		VTMR_GetTimerValue(&UKFMOTEST_vTMR_s);
#endif
}
/*#### |End  | <-- Секция - "Описание глобальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание локальных функций" #####################*/
/*#### |End  | <-- Секция - "Описание локальных функций" #####################*/


/*#### |Begin| --> Секция - "Обработчики прерываний" #########################*/
/*#### |End  | <-- Секция - "Обработчики прерываний" #########################*/

/*############################################################################*/
/*############################ END OF FILE  ##################################*/
/*############################################################################*/
