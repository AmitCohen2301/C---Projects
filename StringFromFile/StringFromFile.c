#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StringFromFile.h"

void readAndPrintStringFromFile()					//Read and print string from file
{
	char* str = createStringFromFile(FILE_NAME);
	if (str != NULL)
	{
		printf("\n\n%s\n\n",str);
		free(str);
	}
	else
		printf("Error in string\n");
}

char* createStringFromFile(const char* fileName)	//Read string from binary file and add string char by char
{
	char* strFromFile = NULL;
	char* newStr;
	int lengthOfChars;
	char chFromFile;
	FILE* fp = fopen(fileName, "rb");
	if (fp == NULL) //Failed to open file
	{
		printf("Failed to open file! \n");
		return NULL;
	}
	if (fread(&lengthOfChars,sizeof(int),1,fp) != 1) //Read int from file
	{
		printf("Failed to read length from file! \n");
		fclose(fp);
		return NULL;
	}
	for (int charNoInFile = 0; charNoInFile < lengthOfChars; charNoInFile++) //Move on all char in file according to length
	{
		if (fread(&chFromFile, sizeof(char), 1, fp) != 1) //Read every char
		{
			printf("Failed to read char from file! \n");
			fclose(fp);
			return NULL;
		}
		newStr = appendCharToString(strFromFile, chFromFile); //Add char to string
		if (strFromFile != NULL) //Free the old str
			free(strFromFile);
		strFromFile = newStr;
	}
	return strFromFile;
}

char* appendCharToString(char* str, char tav)		//Add char to string
{
	int strLength;
	if (str == NULL) //First char to add
		strLength = 0;
	else //Not first char to add
		strLength = (int)strlen(str);
	char* newStr = (char*)malloc((strLength + 2) * sizeof(char)); //Make new string
	if (newStr == NULL) //Not succeed to give dyn allocation
		return NULL;
	for (int charIndex = 0; charIndex < strLength; charIndex++) //Copy old string
		*(newStr + charIndex) = *(str + charIndex);
	*(newStr + strLength) = tav; //Copy the new tav
	*(newStr + strLength + 1) = '\0'; //End the string
	return newStr;
}
