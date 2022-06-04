#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Product.h"
#include "General.h"

const char* typeStr[eNofProductType] = { "Fruit Vegtable", "Fridge", "Frozen", "Shelf" };

void initProduct(Product* pProduct)											//Init new product
{
	initProductNoBarcode(pProduct);
	getBorcdeCode(pProduct->barcode);
}

void initProductNoBarcode(Product* pProduct)								//Init new product without barcode
{
	initProductName(pProduct);
	pProduct->type = getProductType();
	printf("Enter product price and number of items\t");
	scanf("%f %d", &pProduct->price, &pProduct->count);
}

void initProductName(Product* pProduct)										//Init product name
{
	printf("enter product name up to %d chars\n", NAME_LENGTH - 1);
	myGets(pProduct->name, NAME_LENGTH);
}

void printProduct(const Product* pProduct)									//Print the product
{
	printf("%-20s %-10s\t", pProduct->name, pProduct->barcode);
	printf("%-20s %5.2f %10d\n", typeStr[pProduct->type], pProduct->price, pProduct->count);
}

void printProductV(const void* val)											//Print product by casting
{
	const Product* pProduct = *(const Product**)val;
	printProduct(pProduct);
}

void getBorcdeCode(char* code)												//Check barcode is ok and if not ask from user new one
{
	char temp[MAX_STR_LEN];
	char msg[MAX_STR_LEN];
	sprintf(msg, "Code should be of %d length exactly\nUPPER CASE letter and digits\nMust have 3 to 5 digits\n",
		BARCODE_LENGTH);
	int ok = 1;
	int digCount = 0;
	do { //Check the barcode is ok
		ok = 1;
		digCount = 0;
		printf("Enter product barcode ");
		getsStrFixSize(temp, MAX_STR_LEN, msg);
		if (strlen(temp) != BARCODE_LENGTH) //Not in exact length
		{
			puts(msg);
			ok = 0;
		}
		else { //In exact length
			for (int i = 0; i < BARCODE_LENGTH; i++)
			{
				if (!isupper(temp[i]) && !isdigit(temp[i])) //Char is not upper and not digit
				{
					puts(msg);
					ok = 0;
					break;
				}
				if (isdigit(temp[i])) //Char is digit
					digCount++;
			}
		}
		if (digCount < 3 || digCount > 5) //Check that the barcode has number of digits in range of 3 to 5
			ok = 0;
	} while (!ok);
	strcpy(code, temp);
}

eProductType getProductType()												//Get product type from user
{
	int option;
	printf("\n\n");
	do {
		printf("Please enter one of the following types\n");
		for (int i = 0; i < eNofProductType; i++)
			printf("%d for %s\n", i, typeStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofProductType);
	getchar();
	return (eProductType)option;
}

eProductType getProductTypeByNum(int num)									//Get product type by num
{
	switch (num)
	{
	case 0:
		return eFruitVegtable;
	case 1:
		return eFridge;
	case 2:
		return eFrozen;
	case 3:
		return eShelf;
	}
	return eNofProductType;
}

int getProductTypeInInt(eProductType productType)							//Get product type in int
{
	switch (productType)
	{
	case eFruitVegtable:
		return 0;
	case eFridge:
		return 1;
	case eFrozen:
		return 2;
	case eShelf:
		return 3;
	}
	return 4;
}

const char* getProductTypeStr(eProductType type)							//Get product type in string
{
	if (type < 0 || type >= eNofProductType)
		return NULL;
	return typeStr[type];
}

int	isProduct(const Product* pProduct, const char* barcode)					//Check if the barcode is the barcode of the product
{
	if (strcmp(pProduct->barcode, barcode) == 0)
		return 1;
	return 0;
}

void updateProductCount(Product* pProduct)									//Update product count
{
	int count;
	do {
		printf("How many items to add to stock?");
		scanf("%d", &count);
	} while (count < 1);
	pProduct->count += count;
}


void freeProduct(Product* pProduct)											//Free product
{
	//nothing to free!
}

int compareProductsByName(const void* pProduct1, const void* pProduct2)		//Compare products by name
{
	Product* p1 = *(Product**)pProduct1;
	Product* p2 = *(Product**)pProduct2;
	return strcmp(p1->name, p2->name);
}

int compareProductsByBarcode(const void* pProduct1, const void* pProduct2)	//Compare products by barcode
{
	Product* p1 = *(Product**)pProduct1;
	Product* p2 = *(Product**)pProduct2;
	return strcmp(p1->barcode, p2->barcode);
}

int compareProductsByType(const void* pProduct1, const void* pProduct2)		//Compare products by type
{
	Product* p1 = *(Product**)pProduct1;
	Product* p2 = *(Product**)pProduct2;
	return strcmp(getProductTypeStr(p1->type), getProductTypeStr(p2->type));
}

int compareProductsByPrice(const void* pProduct1, const void* pProduct2)	//Compare products by price
{
	Product* p1 = *(Product**)pProduct1;
	Product* p2 = *(Product**)pProduct2;
	if (p1->price > p2->price)
		return 1;
	else
	{
		if (p1->price == p2->price)
			return 0;
	}
	return -1;
}