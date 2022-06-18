#pragma once

#define FILE_NAME "tavs.bin"

void readAndPrintStringFromFile();					//Read and print string from file
char* createStringFromFile(const char* fileName);	//Read string from binary file and add string char by char
char* appendCharToString(char* str, char tav);		//Add char to string