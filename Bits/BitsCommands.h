#pragma once
#include <stdio.h>

typedef unsigned char BYTE;

void printCharAsBinary(unsigned char ch);						//Print char in binary
int getBitFromLeft(unsigned char ch, int index);				//Get bit in X place from left
int getBitFromRight(unsigned char ch, int index);				//Get bit in X place from right
char setBitFromRight(unsigned char ch, int index, int value);	//Set bit in X place from right
unsigned char createMask(int high, int low);					//Create mask