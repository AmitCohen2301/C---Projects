#pragma once

typedef struct
{
	char*	name;
}Customer;

int	initCustomer(Customer* pCustomer);						//Init new customer
void printCustomer(const Customer* pCustomer);				//Print customer
void printCustomerV(const void* pP);						//Print customer by casting
int	isCustomer(const Customer* pCust, const char* name);	//Check if the name is the name of the customer
void freeCustomer(Customer* pCust);							//Free customer
void freeCustomerV(Customer* pCust);						//Free customer by casting