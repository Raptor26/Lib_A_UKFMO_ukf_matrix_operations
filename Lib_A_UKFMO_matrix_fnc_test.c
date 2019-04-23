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
__UKFMO_FPT__ UKFMOTEST_initialMatrix_a[UKFMOTEST_MATRIX_ROW][UKFMOTEST_MATRIX_COLUMN];
UKFMOTEST_MATRIX_S UKFMOTEST_initialMatrix_s;

__UKFMO_FPT__ UKFMOTEST_matrixA_a[UKFMOTEST_MATRIX_ROW][UKFMOTEST_MATRIX_COLUMN];
UKFMOTEST_MATRIX_S UKFMOTEST_matrixA_s;

__UKFMO_FPT__ UKFMOTEST_matrixB_a[UKFMOTEST_MATRIX_ROW][UKFMOTEST_MATRIX_COLUMN];
UKFMOTEST_MATRIX_S UKFMOTEST_matrixB_s;

__UKFMO_FPT__ UKFMOTEST_matrixC_a[UKFMOTEST_MATRIX_ROW][UKFMOTEST_MATRIX_COLUMN];
UKFMOTEST_MATRIX_S UKFMOTEST_matrixC_s;
/*#### |End  | <-- Секция - "Глобальные переменные" ##########################*/


/*#### |Begin| --> Секция - "Локальные переменные" ###########################*/
/*#### |End  | <-- Секция - "Локальные переменные" ###########################*/


/*#### |Begin| --> Секция - "Прототипы локальных функций" ####################*/
/*#### |End  | <-- Секция - "Прототипы локальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание глобальных функций" ####################*/
void
UKFMOTEST_Test(void)
{
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

	UKFMO_MatrixInverse(
		&UKFMOTEST_matrixC_s,
		&UKFMOTEST_matrixB_s);

	UKFMO_GetCholeskyLow(
		(__UKFMO_FPT__*) UKFMOTEST_matrixB_a,
		(__UKFMO_FPT__*) UKFMOTEST_matrixC_a,
		UKFMOTEST_matrixC_s.numCols);

	/* step10 */
	UKMO_MatrixSubstraction(
		&UKFMOTEST_matrixB_s,
		&UKFMOTEST_initialMatrix_s,
		&UKFMOTEST_initialMatrix_s);
}
/*#### |End  | <-- Секция - "Описание глобальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание локальных функций" #####################*/
/*#### |End  | <-- Секция - "Описание локальных функций" #####################*/


/*#### |Begin| --> Секция - "Обработчики прерываний" #########################*/
/*#### |End  | <-- Секция - "Обработчики прерываний" #########################*/

/*############################################################################*/
/*############################ END OF FILE  ##################################*/
/*############################################################################*/
