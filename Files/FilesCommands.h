#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Text files
//Write
int writeStringToTextFile(char* strToWrite, FILE* fp);						//Write string to text file
int writeIntToTextFile(int intToWrite, FILE* fp);							//Write int to text file
int writeFloatToTextFile(float floatToWrite, FILE* fp);						//Write float to text file
int writeCharToTextFile(char charToWrite, FILE* fp);						//Write char to text file
//Read
void readStringFromTextFile(char* placeToPutStr, int maxLength, FILE* fp);	//Read string from text file
int readIntFromTextFile(int* placeToPutInt, FILE* fp);						//Read int from text file
int readFloatFromTextFile(float* placeToPutFloat, FILE* fp);				//Read float from text file
int readCharFromTextFile(char* placeToPutChar, FILE* fp);					//Read char from text file


//Binary files
//Write
int	writeStringWithLengthBeforeToBinaryFile(char* strToWrite, FILE* fp);	//Write string with length before to binary file
int writeStringToBinaryFile(char* arrToWrite, int sizeOfArr, FILE* fp);		//Write string to binary file
int writeIntToBinaryFile(int numToWrite, FILE* fp);							//Write int to binary file
int writeFloatToBinaryFile(float placeToPutFloatNum, FILE* fp);				//Write float to binary file
//Read
char* readStringByIntFromBinaryFile(FILE* fp);								//Read string by int in file from binary file
int	readStringFromBinaryFile(char* arrToPutIn, int sizeOfArr, FILE* fp);	//Read string from binary file
int readIntFromBinaryFile(int* placeToPutNum, FILE* fp);					//Read int from binary file
int readFloatFromBinaryFile(float* placeToPutFloatNum, FILE* fp);			//Read float from binary file