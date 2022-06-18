#pragma once

typedef struct
{
	int value;
	int length;
}Element;

void useElementsFancInMat();																					//Use elements fanc in matrix
void printElementArr(const Element* arr, int count);															//Print array of elements
Element* createElementArrFromCol(int* mat, int colIndex, int numOfRows, int numOfCols, int* sizeOfFinalArr);	//Create elements array from col num
int numOfElement(int* mat, int colIndex, int rowIndex, int numOfRows, int numOfCols);							//Calc num of elements
Element* addElementToArr(Element* arr, int numToAdd, int numOfElements, int sizeOfArr);							//Add element for array of elements
void printMat(int*mat, int numOfRows, int numOfCols);															//Print matrix