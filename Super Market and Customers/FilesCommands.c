#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilesCommands.h"
#include "General.h"

int	writeStringToFile(char* strToWrite, FILE* fp)					//Write string to file
{
	int length = strlen(strToWrite);
	length++;
	if (writeIntToFile(length, fp) != 1) //Write string length
		return 0;
	if (writeCharsToFile(strToWrite, length, fp) != 1) //Write the string
		return 0;
	return 1;
}

int writeCharsToFile(char* arrToWrite, int sizeOfArr, FILE* fp)		//Write chars to file
{
	if (fwrite(arrToWrite, sizeof(char), sizeOfArr, fp) != sizeOfArr) //Write the chars
	{
		fclose(fp);
		return 0;
	}
	return 1;
}

int writeIntToFile(int numToWrite, FILE* fp)						//Write int to file
{
	if (fwrite(&numToWrite, sizeof(int), 1, fp) != 1) //Write the int
	{
		fclose(fp);
		return 0;
	}
	return 1;
}

float writeFloatToFile(float placeToPutFloatNum, FILE* fp)			//Write float to file
{
	if (fwrite(&placeToPutFloatNum, sizeof(float), 1, fp) != 1) //Write the float
	{
		fclose(fp);
		return 0;
	}
	return 1;
}

char* readStringFromFile(FILE* fp)									//Read string from file
{
	char* str;
	int length;
	if (readIntFromFile(&length, fp) != 1) //Read length of string
		return NULL;
	str = (char*)malloc((length) * sizeof(char));
	if (!str)
	{
		fclose(fp);
		return NULL;
	}
	if (fread(str, sizeof(char), length, fp) != length) //Read the string
	{
		fclose(fp);
		return NULL;
	}
	return str;
}

int	readCharsFromFile(char* arrToPutIn, int sizeOfArr, FILE* fp)	//Read chars from file
{
	if (fread(arrToPutIn, sizeof(char), sizeOfArr, fp) != sizeOfArr) //Read the chars
	{
		fclose(fp);
		return 0;
	}
	return 1;
}

int readIntFromFile(int* placeToPutNum, FILE* fp)					//Read int from file
{
	if (fread(placeToPutNum, sizeof(int), 1, fp) != 1) //Read the int
	{
		fclose(fp);
		return 0;
	}
	return 1;
}

float readFloatFromFile(float* placeToPutFloatNum, FILE* fp)		//Read float from file
{
	if (fread(placeToPutFloatNum, sizeof(float), 1, fp) != 1) //Read the float
	{
		fclose(fp);
		return 0;
	}
	return 1;
}