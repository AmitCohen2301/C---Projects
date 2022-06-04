#ifndef __GENERAL__
#define __GENERAL__

#define MAX_STR_LEN 255

char* getStrExactLength(const char* msg);									//Get string in exact length
char* getsStrFixSize(char* buffer, int size, const char* msg);				//Get string in fix size and show the msg
char* myGets(char* buffer, int size);										//Get string to buffer in max size
char* getDynStr(char* str);													//Get the string in dynamic allocation
char** splitCharsToWordsBySpace(char* str, int* pCount, int* pTotalLength);	//Split the string to words according to space
char** splitCharsToWords(char* str, int* pCount, const char* del);			//Split the string to words according to del

#endif