clear all;
rowNumb     = 7;
columnNumb  = 7;

% step1
UKFMOTEST_initialMatrix_a = zeros(rowNumb, columnNumb);

% step2
UKFMOTEST_initialMatrix_a = eye(rowNumb, columnNumb);

%step3
UKFMOTEST_initialMatrix_a = UKFMOTEST_initialMatrix_a * 0.33;

% step4
UKFMOTEST_matrixA_a = zeros(rowNumb, columnNumb);
UKFMOTEST_matrixA_a(1,1) = 0.55;
UKFMOTEST_matrixA_a(1,2) = 0.65;
UKFMOTEST_matrixA_a(1,3) = 0.75;
UKFMOTEST_matrixA_a(1,4) = 0.85;
UKFMOTEST_matrixA_a(1,5) = 0.95;

UKFMOTEST_matrixA_a(2,1) = -0.55;
UKFMOTEST_matrixA_a(2,2) = -0.65;
UKFMOTEST_matrixA_a(2,3) = -0.75;
UKFMOTEST_matrixA_a(2,4) = -0.85;
UKFMOTEST_matrixA_a(2,5) = -0.95;

UKFMOTEST_matrixA_a(5,1) = UKFMOTEST_matrixA_a(5,1) + 0.55;
UKFMOTEST_matrixA_a(4,2) = UKFMOTEST_matrixA_a(4,2) + 0.65;
UKFMOTEST_matrixA_a(3,3) = UKFMOTEST_matrixA_a(3,3) + 0.75;
UKFMOTEST_matrixA_a(2,4) = UKFMOTEST_matrixA_a(2,4) + 0.85;
UKFMOTEST_matrixA_a(1,5) = UKFMOTEST_matrixA_a(1,5) + 0.95;

% step5 
UKFMOTEST_matrixA_a = UKFMOTEST_initialMatrix_a * UKFMOTEST_matrixA_a;

%step6
UKFMOTEST_initialMatrix_a = UKFMOTEST_matrixA_a';

%step7
UKFMOTEST_matrixB_a = UKFMOTEST_initialMatrix_a * UKFMOTEST_matrixA_a;

%step8
UKFMOTEST_matrixC_a = zeros(rowNumb, columnNumb);
UKFMOTEST_matrixC_a(1,1) = 0.514428619342896;
UKFMOTEST_matrixC_a(2,2) = 0.514428619342896;
UKFMOTEST_matrixC_a(3,3) = 0.514428619342896;
UKFMOTEST_matrixC_a(4,4) = 0.514428619342896;
UKFMOTEST_matrixC_a(5,5) = 0.514428619342896;
UKFMOTEST_matrixC_a(6,6) = 0.514428619342896;
UKFMOTEST_matrixC_a(7,7) = 0.514428619342896;

%step 9
UKFMOTEST_matrixB_a = inv(UKFMOTEST_matrixC_a);

UKFMOTEST_matrixB_a = chol(UKFMOTEST_matrixB_a, 'lower');

%step 10
UKFMOTEST_initialMatrix_a = UKFMOTEST_matrixB_a - UKFMOTEST_initialMatrix_a;

