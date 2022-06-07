#define _CRT_SECURE_NO_WARNINGS
#include "BitsCommands.h"

void printCharAsBinary(unsigned char ch)												//Print char in binary
{
	unsigned char temp;
	printf("The char '%c' in binary is: ", ch);
	for (int i = 0; i < 8; i++)
	{
		temp = ch << i;
		temp = temp >> 7;
		printf("%d", (int)temp);
	}
	printf("\n");
}

int getBitFromLeft(unsigned char ch, int index)											//Get bit in X place from left
{
	unsigned char temp = ch << index;
	temp >>= 7;
	return temp;
}

int getBitFromRight(unsigned char ch, int index)										//Get bit in X place from right
{
	unsigned char mask = 1; // 00000001
	mask = mask << index;
	if (ch & mask == 0)
		return 0;
	else
		return 1;
}

char setBitFromRight(unsigned char ch, int index, int value)							//Set bit in X place from right
{
	unsigned char mask = 1; // 00000001
	unsigned char result;
	mask <<= index;
	if (value == 1)
		result = ch | mask;
	else
	{
		mask = ~mask;
		result = ch & mask;
	}
	return result;
}

unsigned char createMask(int high, int low)												//Create mask
{
	return (1 << (high + 1)) - (1 << low);
}

unsigned int compressTwoIntWithMaxTwoBytesEach(unsigned int num1, unsigned int num2)	//Compress two int to one
{
	unsigned int fixNum1 = num1 & 0x1111111111111111;
	unsigned int fixNum2 = num2 & 0x1111111111111111;
	return (fixNum1 << 16) | fixNum2;
}

void unCompressTwoIntFromOne(unsigned int num, unsigned int* num1, unsigned int* num2)	//Uncompress two int from one
{
	*num1 = num >> 16;
	*num2 = num & 0x1111111111111111;
}

unsigned char compressTwoCharWithMaxFourBitsEach(unsigned char ch1, unsigned char ch2)	//Compress two chars to one
{
	unsigned char fixCh1 = ch1 & 0x1111;
	unsigned char fixCh2 = ch2 & 0x1111;
	return (fixCh1 << 4) | fixCh2;
}

void unCompressTwoCharFromOne(unsigned char ch, unsigned char* ch1, unsigned char* ch2)	//Uncompress two char from one
{
	*ch1 = ch >> 4;
	*ch2 = ch & 0x1111;
}