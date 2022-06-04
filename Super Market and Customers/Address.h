#pragma once

typedef struct										//Define the address struct
{
	int		num;
	char*	street;
	char*	city;
}Address;

int	initAddress(Address* pAd);						//Init new address
void printAddress(const Address* pAd);				//Print address
void freeAddress(Address* pAd);						//Free address
int	checkElements(char**  elements, int count);		//Check every element in address is correct
char* fixAddressParam(char* param);					//Fix the address form
void freeElements(char**  elements, int count);		//Free elements in address array