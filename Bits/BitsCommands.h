#pragma once
#include <stdio.h>

typedef unsigned char BYTE;

void printCharAsBinary(unsigned char ch);												//Print char in binary
int getBitFromLeft(unsigned char ch, int index);										//Get bit in X place from left
int getBitFromRight(unsigned char ch, int index);										//Get bit in X place from right
char setBitFromRight(unsigned char ch, int index, int value);							//Set bit in X place from right
unsigned char createMask(int high, int low);											//Create mask
unsigned int compressTwoIntWithMaxTwoBytesEach(unsigned int num1, unsigned int num2);	//Compress two int to one
void unCompressTwoIntFromOne(unsigned int num, unsigned int* num1, unsigned int* num2);	//Uncompress two int from one
unsigned char compressTwoCharWithMaxFourBitsEach(unsigned char ch1, unsigned char ch2);	//Compress two chars to one
void unCompressTwoCharFromOne(unsigned char ch, unsigned char* ch1, unsigned char* ch2);//Uncompress two char from one