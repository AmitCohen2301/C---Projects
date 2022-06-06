#define _CRT_SECURE_NO_WARNINGS
#include "BitsCommands.h"

void printCharAsBinary(unsigned char ch)						//Print char in binary
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

int getBitFromLeft(unsigned char ch, int index)					//Get bit in X place from left
{
	unsigned char temp = ch << index;
	temp >>= 7;
	return temp;
}

int getBitFromRight(unsigned char ch, int index)				//Get bit in X place from right
{
	unsigned char mask = 1; // 00000001
	mask = mask << index;
	if (ch & mask == 0)
		return 0;
	else
		return 1;
}

char setBitFromRight(unsigned char ch, int index, int value)	//Set bit in X place from right
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

unsigned char createMask(int high, int low)						//Create mask
{
	return (1 << (high + 1)) - (1 << low);
}