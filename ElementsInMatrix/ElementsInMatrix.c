#include <stdio.h>
#include <stdlib.h>
#include "ElementsInMatrix.h"

#define R 8
#define C 7

void useElementsFancInMat()																						//Use elements fanc in matrix
{
	int mat[R][C] = {	{1,2,3,4,5,6,7},
						{1,0,3,6,5,5,7},
						{1,0,3,6,8,5,7},
						{1,0,3,6,9,5,7},
						{0,3,5,7,9,1,7},
						{0,4,5,7,9,1,7},
						{1,4,5,6,1,3,7},
						{1,0,5,6,0,3,7} };

	printMat(&mat[0][0], R, C);
	int sizeOfFinal = 0;
	Element* elementArr;
	printf("Elements: \n");
	for (int colNum = 0; colNum < C; colNum++) //Move on each col
	{
		printf("In col number %d ", colNum);
		elementArr = createElementArrFromCol(&mat[0][0], colNum, R, C, &sizeOfFinal);
		printElementArr(elementArr, sizeOfFinal);
		free(elementArr);
	}
}

void printElementArr(const Element* arr, int count)																//Print array of elements
{
	printf("There are %d elements:\t", count);
	for (int i = 0; i < count; i++)
		printf("{%d , %d}\t", arr[i].value, arr[i].length);

	printf("\n");
}

Element* createElementArrFromCol(int* mat, int colIndex, int numOfRows, int numOfCols, int* sizeOfFinalArr)		//Create elements array from col num
{
	Element* arrOfElements = NULL;
	int rowNumIndex = 0;
	int numOfElements = 0;
	while (rowNumIndex < numOfRows) //Move on every row until end
	{
		int numOfElementsInRow = numOfElement(mat, colIndex, rowNumIndex, numOfRows, numOfCols); //Check how many elements in row
		arrOfElements = addElementToArr(arrOfElements, *(mat + rowNumIndex * numOfCols + colIndex), numOfElementsInRow, numOfElements); //Add element to arr
		rowNumIndex += numOfElementsInRow; //Add the number of rows that checked
		numOfElements++; //Increase the length of array
	}
	*sizeOfFinalArr = numOfElements;
	return arrOfElements;
}

int numOfElement(int* mat, int colIndex, int rowNumIndex, int numOfRows, int numOfCols)							//Calc num of elements
{
	int numToCheck = *(mat + rowNumIndex * numOfCols + colIndex); //Get the num to check
	int numOfElementsInRow = 0;
	for (int rowNum = rowNumIndex; rowNum < numOfRows; rowNum++) //Move on every row until end
	{
		if (*(mat + rowNum * numOfCols + colIndex) == numToCheck) //Same number
			numOfElementsInRow++;
		else //End of element
			return numOfElementsInRow;
	}
	return numOfElementsInRow;
}

Element* addElementToArr(Element* arr, int numToAdd, int numOfElements, int sizeOfArr)							//Add element for array of elements
{
	Element* arrOfElements = (Element*)realloc(arr, (sizeOfArr + 1) * sizeof(Element));
	if (!arrOfElements) //Not succeed to give dyn allocation
		return 0;

	arrOfElements[sizeOfArr].value = numToAdd; //Update the new cell
	arrOfElements[sizeOfArr].length = numOfElements; //Update the new cell
	return arrOfElements;
}

void printMat(int*mat, int numOfRows, int numOfCols)															//Print matrix
{
	printf("The matrix is: \n");
	for (int rowNum = 0; rowNum < numOfRows; rowNum++) //Move on every row
	{
		for (int colNum = 0; colNum < numOfCols; colNum++) //Move on every col
		{
			printf("%5d", *(mat + rowNum * numOfCols + colNum));
		}
		printf("\n");
	}
	printf("\n");
}