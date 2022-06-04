#pragma once

#define EXIT -1

typedef enum
{
	eShowSuperMarket, eAddProduct, eAddCustomer, eCustomerDoShopping,
	ePrintProductByType, eSortProductsBy, eBinarySearchForProduct, eNofOptions
} eMenuOptions;

const char* menuStrings[eNofOptions];

int menu();