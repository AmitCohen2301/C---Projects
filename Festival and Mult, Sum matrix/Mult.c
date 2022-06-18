#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrices.h"
#include "Mult.h"

int calcCell(int *matA, int *matB, int rowInA, int colInB, int sizeOfMat)	//Calc the cell value
{
	int sum = 0;
	int rowNum, colNum, calcNo;
	for (rowNum = 0; rowNum < rowInA; rowNum++) //Get to the right row num in A to calc
		matA += sizeOfMat;
	for (colNum = 0; colNum < colInB; colNum++) //Get to the right col num in B to calc
		matB++;
	for (calcNo = 0; calcNo < sizeOfMat; calcNo++) //Calc
	{
		sum += (*matA) * (*matB);
		matA++; //Move the col in A
		matB += sizeOfMat; //Move the row in B
	}
	return sum;
}

void multMatrix(int *matA, int *matB, int *matC, int sizeOfMat)				//Mult two matrix
{
	int rowNumInC, colNumInC;
	for (rowNumInC = 0; rowNumInC < sizeOfMat; rowNumInC++)
	{
		for (colNumInC = 0; colNumInC < sizeOfMat; colNumInC++)
		{
			*matC = calcCell((int*)matA, (int*)matB, rowNumInC, colNumInC, sizeOfMat); //Calc for each place in C
			matC++;
		}
	}
}

void doMultMat()															//Do mult in two matrix
{
	int matA[N][N];
	int matB[N][N];
	int matC[N][N];
	int sizeOfMat;
	printf("\nEnter size of A matrix between 1 and %d \n", N);
	scanf("%d", &sizeOfMat);
	while ((sizeOfMat < 1) || (sizeOfMat > N)) //Check the input is in range
	{
		printf("You entered invalid size of matrix! \n");
		printf("Enter size of A matrix between 1 and %d \n", N);
		scanf("%d", &sizeOfMat);
	}
	fflush(stdin);
	srand(time(NULL));
	printf("**********************************\n");
	printf("The matrices are filled in numbers between %d and %d \n", MIN_NUM_IN_ARR, MAX_NUM_IN_ARR);
	fillMat((int*)matA, sizeOfMat, sizeOfMat);
	fillMat((int*)matB, sizeOfMat, sizeOfMat);
	printf("************ matrix A ************\n");
	printMat((int*)matA, sizeOfMat, sizeOfMat);
	printf("************ matrix B ************\n");
	printMat((int*)matB, sizeOfMat, sizeOfMat);
	printf("********** result matrix **********\n");
	multMatrix((int*)matA, (int*)matB, (int*)matC, sizeOfMat); //Do mult AxB and put in C
	printMat((int*)matC, sizeOfMat, sizeOfMat);
}