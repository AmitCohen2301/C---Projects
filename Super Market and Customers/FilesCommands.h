#pragma once
#include <stdio.h>

int	writeStringToFile(char* strToWrite, FILE* fp);					//Write string to file
int writeCharsToFile(char* arrToWrite, int sizeOfArr, FILE* fp);	//Write chars to file
int writeIntToFile(int numToWrite, FILE* fp);						//Write int to file
float writeFloatToFile(float placeToPutFloatNum, FILE* fp);		//Write float to file
char* readStringFromFile(FILE* fp);									//Read string from file
int	readCharsFromFile(char* arrToPutIn, int sizeOfArr, FILE* fp);	//Read chars from file
int readIntFromFile(int* placeToPutNum, FILE* fp);					//Read int from file
float readFloatFromFile(float* placeToPutFloatNum, FILE* fp);		//Read float from file