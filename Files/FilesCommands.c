#define _CRT_SECURE_NO_WARNINGS
#include "FilesCommands.h"

//Text Files
//Write
int writeStringToTextFile(char* strToWrite, FILE* fp)						//Write string to text file
{
	return fprintf(fp, "%s\n", strToWrite);
}

int writeIntToTextFile(int intToWrite, FILE* fp)							//Write int to text file
{
	return fprintf(fp, "%d\n", intToWrite);
}

int writeFloatToTextFile(float floatToWrite, FILE* fp)						//Write float to text file
{
	return fprintf(fp, "%f\n", floatToWrite);
}

int writeCharToTextFile(char charToWrite, FILE* fp)							//Write char to text file
{
	return fprintf(fp, "%c\n", charToWrite);
}

//Read
void readStringFromTextFile(char* placeToPutStr, int maxLength, FILE* fp)	//Read string from text file
{
	fgets(placeToPutStr, maxLength, fp);
	strtok(placeToPutStr, "\n");
}

int readIntFromTextFile(int* placeToPutInt, FILE* fp)						//Read int from text file
{
	char clearEnterAfterInput;
	int valueToReturn = fscanf(fp, "%d", placeToPutInt);
	fscanf(fp, "%c", &clearEnterAfterInput);
	return valueToReturn;
}

int readFloatFromTextFile(float* placeToPutFloat, FILE* fp)					//Read float from text file
{
	char clearEnterAfterInput;
	int valueToReturn = fscanf(fp, "%f", placeToPutFloat);
	fscanf(fp, "%c", &clearEnterAfterInput);
	return valueToReturn;
}

int readCharFromTextFile(char* placeToPutChar, FILE* fp)					//Read char from text file
{
	char clearEnterAfterInput;
	int valueToReturn = fscanf(fp, "%c", placeToPutChar);
	fscanf(fp, "%c", &clearEnterAfterInput);
	return valueToReturn;
}


//Binary Files
//Write
int	writeStringWithLengthBeforeToBinaryFile(char* strToWrite, FILE* fp)		//Write string with length before to binary file
{
	int length = strlen(strToWrite);
	length++;
	if (writeIntToBinaryFile(length, fp) != 1) //Write string length
		return 0;
	if (writeStringToBinaryFile(strToWrite, length, fp) != 1) //Write the string
		return 0;
	return 1;
}

int writeStringToBinaryFile(char* arrToWrite, int sizeOfArr, FILE* fp)		//Write string to binary file
{
	if (fwrite(arrToWrite, sizeof(char), sizeOfArr, fp) != sizeOfArr) //Write the string
	{
		fclose(fp);
		return 0;
	}
	return 1;
}

int writeIntToBinaryFile(int numToWrite, FILE* fp)							//Write int to binary file
{
	if (fwrite(&numToWrite, sizeof(int), 1, fp) != 1) //Write the int
	{
		fclose(fp);
		return 0;
	}
	return 1;
}

int writeFloatToBinaryFile(float placeToPutFloatNum, FILE* fp)				//Write float to binary file
{
	if (fwrite(&placeToPutFloatNum, sizeof(float), 1, fp) != 1) //Write the float
	{
		fclose(fp);
		return 0;
	}
	return 1;
}

//Read
char* readStringByIntFromBinaryFile(FILE* fp)								//Read string by int in file from binary file
{
	char* str;
	int length;
	if (readIntFromBinaryFile(&length, fp) != 1) //Read length of string
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

int	readStringFromBinaryFile(char* arrToPutIn, int sizeOfArr, FILE* fp)		//Read string from binary file
{
	if (fread(arrToPutIn, sizeof(char), sizeOfArr, fp) != sizeOfArr) //Read the string
	{
		fclose(fp);
		return 0;
	}
	return 1;
}

int readIntFromBinaryFile(int* placeToPutNum, FILE* fp)						//Read int from binary file
{
	if (fread(placeToPutNum, sizeof(int), 1, fp) != 1) //Read the int
	{
		fclose(fp);
		return 0;
	}
	return 1;
}

int readFloatFromBinaryFile(float* placeToPutFloatNum, FILE* fp)			//Read float from binary file
{
	if (fread(placeToPutFloatNum, sizeof(float), 1, fp) != 1) //Read the float
	{
		fclose(fp);
		return 0;
	}
	return 1;
}