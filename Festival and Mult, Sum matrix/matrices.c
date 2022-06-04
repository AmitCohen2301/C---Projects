#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrices.h"

void fillMat(int *mat, int numOfRows, int numOfCols)
{
	int placeInMat;
	for(placeInMat = 0; placeInMat < numOfRows * numOfCols; placeInMat++)
	{
		*mat = (rand() % (MAX_NUM_IN_ARR + 1)) - MIN_NUM_IN_ARR;
		mat++;
	}
}

void printMat(int *mat, int numOfRows, int numOfCols)
{
	int rowNum, colNum;
	for(rowNum = 0; rowNum < numOfRows; rowNum++)
	{
		for(colNum = 0; colNum < numOfCols; colNum++)
		{
			printf("%5d", *mat);
			mat++;
		}
		printf("\n");
	}
	printf("\n");
}

