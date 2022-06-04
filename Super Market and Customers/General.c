#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "General.h"

char* getStrExactLength(const char* msg)									//Get string in exact length
{
	char* str;
	char temp[MAX_STR_LEN];
	getsStrFixSize(temp, MAX_STR_LEN, msg);
	str = getDynStr(temp);
	return str;
}

char* getDynStr(char* str)													//Get the string in dynamic allocation
{
	char* theStr;
	theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (!theStr)
		return NULL;
	strcpy(theStr, str);
	return theStr;
}

char* getsStrFixSize(char* buffer, int size, const char* msg)				//Get string in fix size and show the msg
{
	puts(msg);
	return myGets(buffer, size);
}

char* myGets(char* buffer, int size)										//Get string to buffer in max size
{
	if (buffer != NULL && size > 0)
	{
		if (fgets(buffer, size, stdin))
		{
			buffer[strcspn(buffer, "\n")] = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}

char** splitCharsToWordsBySpace(char* str, int* pCount, int* pTotalLength)	//Split the string to words according to space
{
	char temp[255];
	char* delimiters = " ";
	char* word;
	int count = 0;
	strcpy(temp, str);
	char** wordsArray = NULL;
	*pTotalLength = 0;
	word = strtok(temp, delimiters);
	while (word != NULL)
	{
		wordsArray = (char**)realloc(wordsArray, (count + 1) * sizeof(char*));
		if (!wordsArray)
			return 0;
		wordsArray[count] = getDynStr(word);
		count++;
		*pTotalLength += (int)strlen(word);
		word = strtok(NULL, delimiters);
	}
	*pCount = count;
	return wordsArray;
}

char** splitCharsToWords(char* str, int* pCount, const char* del)			//Split the string to words according to del
{
	char temp[255];
	char* word;
	int count = 0;
	strcpy(temp, str);
	char** wordsArray = NULL;
	word = strtok(temp, del);
	while (word != NULL)
	{
		wordsArray = (char**)realloc(wordsArray, (count + 1) * sizeof(char*));
		if (!wordsArray)
			return 0;
		wordsArray[count] = getDynStr(word);
		count++;
		word = strtok(NULL, del);
	}
	*pCount = count;
	return wordsArray;
}