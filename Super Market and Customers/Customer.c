#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Customer.h"
#include "General.h"

int	initCustomer(Customer* pCustomer)						//Init new customer
{
	pCustomer->name = getStrExactLength("Enter customer name\n");
	if (!pCustomer->name)
		return 0;
	return 1;
}

void printCustomer(const Customer* pCustomer)				//Print customer
{
	printf("Name: %s\n", pCustomer->name);
}

void printCustomerV(const void* pP)							//Print customer by casting
{
	const Customer* pCustomer = (const Customer*)pP;
	printCustomer(pCustomer);
}

int isCustomer(const Customer* pCust, const char* name)		//Check if the name is the name of the customer
{
	if (strcmp(pCust->name, name) == 0)
		return 1;
	return 0;
}

void freeCustomer(Customer* pCust)							//Free customer
{
	free(pCust->name);
}

void freeCustomerV(Customer* pCust)							//Free customer by casting
{
	Customer* pCustomer = (Customer*)pCust;
	freeCustomer(pCustomer);
}