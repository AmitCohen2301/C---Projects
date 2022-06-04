#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrices.h"
#include "exe2.h"

void sumMatrix(int *matA, int *matB, int *matC, int numOfRows, int numOfCols)
{
	int numOfRow, numOfCol;
	for(numOfRow = 0; numOfRow < numOfRows; numOfRow++)
	{
		for(numOfCol = 0; numOfCol < numOfCols; numOfCol++)
		{
			*matC = (*matA) + (*matB); //Do sum for each cell in C
			matA++;
			matB++;
			matC++;
		}
	}
}

void doSumMat()
{
	int matA[ROWS][COLS];
	int matB[ROWS][COLS];
	int matC[ROWS][COLS];
	int numOfRows, numOfCols;
	printf("\nEnter number of rows of A matrix between 1 and %d \n", ROWS);
	scanf("%d", &numOfRows);
	while((numOfRows < 1) || (numOfRows > ROWS)) //Check the input is in range
	{
		printf("You entered invalid number of rows of A matrix! \n");
		printf("Enter number of rows of A matrix between 1 and %d \n", ROWS);
		scanf("%d", &numOfRows);
	}
	fflush(stdin);
	printf("Enter number of cols of A matrix between 1 and %d \n", COLS);
	scanf("%d", &numOfCols);
	while((numOfCols < 1) || (numOfCols > COLS)) //Check the input is in range
	{
		printf("You entered invalid number of cols of A matrix! \n");
		printf("Enter number of cols of A matrix between 1 and %d \n", COLS);
		scanf("%d", &numOfCols);
	}
	fflush(stdin);
	srand(time(NULL));
	printf("**********************************\n");
	printf("The matrices are filled in numbers between %d and %d \n", MIN_NUM_IN_ARR, MAX_NUM_IN_ARR);
	fillMat((int*)matA, numOfRows, numOfCols);
	fillMat((int*)matB, numOfRows, numOfCols);
	printf("************ matrix A ************\n");
	printMat((int*)matA, numOfRows, numOfCols);
	printf("************ matrix B ************\n");
	printMat((int*)matB, numOfRows, numOfCols);
	printf("********** result matrix **********\n");
	sumMatrix((int*)matA, (int*)matB, (int*)matC, numOfRows, numOfCols); //Do the sum A+B and put in C
	printMat((int*)matC, numOfRows, numOfCols);
}
