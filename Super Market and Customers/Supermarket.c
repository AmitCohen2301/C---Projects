#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Supermarket.h"
#include "Product.h"
#include "Customer.h"
#include "Address.h"
#include "General.h"
#include "ShoppingCart.h"
#include "FilesCommands.h"

const char* sortTypeStr[eNofSortType] = { "Name", "Barcode", "Type", "Price", "Nothing" };

int	initSuperMarket(SuperMarket* pMarket)								//Init new supermarket
{
	pMarket->customerCount = 0;
	pMarket->customerArr = NULL;
	pMarket->productCount = 0;
	pMarket->productArr = NULL;
	pMarket->sortBy = eByNothing;
	pMarket->name = getStrExactLength("Enter market name");
	initAddress(&pMarket->location);
	return 1;
}

void printSuperMarket(const SuperMarket* pMarket)						//Print super market
{
	printf("Super Market Name: %s\t", pMarket->name);
	printf("Address: ");
	printAddress(&pMarket->location);
	printf("\n");
	printf("The products sort by: %s \n", getSortTypeStr(pMarket->sortBy));
	generalArrayFunction((void*)pMarket->productArr, pMarket->productCount, sizeof(Product*), printProductV);
	printf("\n");
	generalArrayFunction((void*)pMarket->customerArr, pMarket->customerCount, sizeof(Customer), printCustomerV);
}

int	addProduct(SuperMarket* pMarket)									//Add product to super market
{
	char barcode[BARCODE_LENGTH + 1];
	Product* pProd = getProductFromUser(pMarket, barcode);
	if (pProd != NULL) //This barcode exist in stock
		updateProductCount(pProd);
	else { //new product to stock
		if (!addNewProduct(pMarket, barcode))
			return 0;
		sortProductsBy(pMarket, pMarket->sortBy);
	}
	return 1;
}

int	addNewProduct(SuperMarket* pMarket, const char* barcode)				//Add new product to super market
{
	pMarket->productArr = (Product**)realloc(pMarket->productArr, (pMarket->productCount + 1) * sizeof(Product*));
	if (!pMarket->productArr)
		return 0;
	Product* pProd = (Product*)calloc(1, sizeof(Product));
	if (!pProd)
	{
		free(pMarket->productArr);
		return 0;
	}
	strcpy(pProd->barcode, barcode);
	initProductNoBarcode(pProd);
	pMarket->productArr[pMarket->productCount] = pProd;
	pMarket->productCount++;
	return 1;
}

int	addCustomer(SuperMarket* pMarket)									//Add customer to super market
{
	pMarket->customerArr = (Customer*)realloc(pMarket->customerArr, (pMarket->customerCount + 1) * sizeof(Customer));
	if (!pMarket->customerArr)
		return 0;
	if (!initCustomer(&pMarket->customerArr[pMarket->customerCount]))
		return 0;
	pMarket->customerCount++;
	return 1;
}

void doShopping(SuperMarket* pMarket)									//Do shopping procedure
{
	if (pMarket->customerCount == 0) //No customers
	{
		printf("No customer listed to market\n");
		return;
	}
	if (pMarket->productCount == 0) //No products
	{
		printf("No products in market - cannot shop\n");
		return;
	}
	Customer* pCustomer = getCustomerWhoShop(pMarket);
	if (!pCustomer) //Enter non customer
	{
		printf("this customer not listed\n");
		return;
	}
	ShoppingCart cart;
	initCart(&cart);
	fillCart(pMarket, &cart);
	printf("---------- Shopping ended ----------\n");
	printf("---------- Cart info and bill for %s ----------\n", pCustomer->name);
	printShoppingCart(&cart);
	printf("!!! --- Payment was recived!!!! --- \n");
	freeShoppingCart(&cart);
	printf("---------- Shopping  ----------\n");
}

Customer* getCustomerWhoShop(SuperMarket* pMarket)						//Get customer from super market
{
	generalArrayFunction((void*)pMarket->customerArr, pMarket->customerCount, sizeof(Customer), printCustomerV);
	char name[MAX_STR_LEN];
	getsStrFixSize(name, sizeof(name), "Who is shopping? Enter cutomer name\n");
	Customer* pCustomer = FindCustomerByName(pMarket, name);
	return pCustomer;
}

void fillCart(SuperMarket* pMarket, ShoppingCart* pCart)				//Put items in cart
{
	generalArrayFunction((void*)pMarket->productArr, pMarket->productCount, sizeof(Product*), printProductV);
	char op;
	while (1)
	{
		printf("Do you want to shop for a product? y/Y, anything else to exit!!\t");
		do {
			scanf("%c", &op);
		} while (isspace(op));
		getchar(); //clean the enter
		if (op != 'y' && op != 'Y') //Stop put products in cart
			break;
		int count;
		Product* pProd = getProductAndCount(pMarket, &count);
		if (pProd)
		{
			if (!addItemToCart(pCart, pProd->name, pProd->price, count))
			{
				printf("Error adding item\n");
				return;
			}
			pProd->count -= count; //item bought!!!
		}
	}
}

Product* getProductAndCount(SuperMarket* pMarket, int* pCount)			//Get product and count from super market
{
	char barcode[BARCODE_LENGTH + 1];
	Product* pProd = getProductFromUser(pMarket, barcode);
	if (pProd == NULL) //No product with that barcode
	{
		printf("No such product\n");
		return NULL;
	}
	if (pProd->count == 0) //No more units from product in stock
	{
		printf("This product out of stock\n");
		return NULL;
	}
	int count;
	do {
		printf("How many items do you want? max %d\n", pProd->count);
		scanf("%d", &count);
	} while (count < 0 || count > pProd->count);
	*pCount = count;
	return pProd;
}

void printProductByType(SuperMarket* pMarket)							//Print all product from a specific type
{
	if (pMarket->productCount == 0) //No products
	{
		printf("No products in market\n");
		return;
	}
	eProductType type = getProductType();
	int count = 0;
	for (int i = 0; i < pMarket->productCount; i++)
	{
		if (pMarket->productArr[i]->type == type)
		{
			count++;
			printProduct(pMarket->productArr[i]);
		}
	}
	if (count == 0) //No products from the type
		printf("There are no product of type %s in market %s\n", getProductTypeStr(type), pMarket->name);
}

Product* getProductFromUser(SuperMarket* pMarket, char* barcode)		//Get product from user by barcode
{
	getBorcdeCode(barcode);
	return getProductByBarcode(pMarket, barcode);
}

void freeMarket(SuperMarket* pMarket)									//Free the super market
{
	free(pMarket->name);
	freeAddress(&pMarket->location); //Free the address
	for (int i = 0; i < pMarket->productCount; i++) //Free all products
	{
		freeProduct(pMarket->productArr[i]);
		free(pMarket->productArr[i]);
	}
	free(pMarket->productArr);
	generalArrayFunction((void*)pMarket->customerArr, pMarket->customerCount, sizeof(Customer), freeCustomerV);
	free(pMarket->customerArr);
}

void getUniquBarcode(char* barcode, SuperMarket* pMarket)				//Check the barcode is unique
{
	int cont = 1;
	while (cont)
	{
		getBorcdeCode(barcode);
		int index = getProductIndexByBarcode(pMarket, barcode);
		if (index == -1)
			cont = 0;
		else
			printf("This product already in market\n");
	}
}

int getProductIndexByBarcode(SuperMarket* pMarket, const char* barcode)//Get product index by the barcode
{
	for (int i = 0; i < pMarket->productCount; i++)
	{
		if (isProduct(pMarket->productArr[i], barcode))
			return i;
	}
	return -1;

}

Product* getProductByBarcode(SuperMarket* pMarket, const char* barcode)//Get product by the barcode
{
	for (int i = 0; i < pMarket->productCount; i++)
	{
		if (isProduct(pMarket->productArr[i], barcode))
			return pMarket->productArr[i];
	}
	return NULL;

}

Customer* FindCustomerByName(SuperMarket* pMarket, const char* name)	//Find customer according to name
{
	for (int i = 0; i < pMarket->customerCount; i++)
	{
		if (isCustomer(&pMarket->customerArr[i], name))
			return &pMarket->customerArr[i];
	}
	return  NULL;
}

eSortType getSortType()													//Get sort type from user
{
	int option;
	printf("\n\n");
	do {
		printf("Please enter one of the following sort types\n");
		for (int i = 0; i < eNofSortType; i++)
			printf("%d for sort by %s\n", i, sortTypeStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofSortType);
	getchar();
	return (eSortType)option;
}

eSortType getSortTypeByNum(int numOfSortType)							//Get sort type by number
{
	switch (numOfSortType)
	{
	case 0:
		return eByName;
	case 1:
		return eByBarcode;
	case 2:
		return eByType;
	case 3:
		return eByPrice;
	case 4:
		return eByNothing;
	}
	return eNofSortType;
}

int getSortTypeNum(eSortType sortType)									//Get sort type num
{
	switch (sortType)
	{
	case eByName:
		return 0;
	case eByBarcode:
		return 1;
	case eByType:
		return 2;
	case eByPrice:
		return 3;
	case eByNothing:
		return 4;
	}
	return 5;
}

const char*	getSortTypeStr(eSortType type)								//Get sort type in string
{
	if (type < 0 || type >= eNofSortType)
		return NULL;
	return sortTypeStr[type];
}

void sortProductsByUser(SuperMarket* pMarket)							//Sort products in super market according to user choice
{
	eSortType typeToSort = getSortType();
	switch (typeToSort)
	{
	case eByName:
		qsort(pMarket->productArr, pMarket->productCount, sizeof(Product*), compareProductsByName);
		break;
	case eByBarcode:
		qsort(pMarket->productArr, pMarket->productCount, sizeof(Product*), compareProductsByBarcode);
		break;
	case eByType:
		qsort(pMarket->productArr, pMarket->productCount, sizeof(Product*), compareProductsByType);
		break;
	case eByPrice:
		qsort(pMarket->productArr, pMarket->productCount, sizeof(Product*), compareProductsByPrice);
		break;
	case eByNothing:
		break;
	}
	pMarket->sortBy = typeToSort;
	printf("Done, the products sort by %s \n", getSortTypeStr(typeToSort));
}

void sortProductsBy(SuperMarket* pMarket, eSortType typeToSort)			//Sort products in super market by specific type
{
	switch (typeToSort)
	{
	case eByName:
		qsort(pMarket->productArr, pMarket->productCount, sizeof(Product*), compareProductsByName);
		break;
	case eByBarcode:
		qsort(pMarket->productArr, pMarket->productCount, sizeof(Product*), compareProductsByBarcode);
		break;
	case eByType:
		qsort(pMarket->productArr, pMarket->productCount, sizeof(Product*), compareProductsByType);
		break;
	case eByPrice:
		qsort(pMarket->productArr, pMarket->productCount, sizeof(Product*), compareProductsByPrice);
		break;
	case eByNothing:
		break;
	}
}

void binarySearchToProduct(SuperMarket* pMarket)						//Binary search to product according to the sort of super market
{
	Product* foundProduct = NULL;
	switch (pMarket->sortBy)
	{
	case eByName:
		foundProduct = searchProductByName(pMarket);
		if (foundProduct != NULL)
		{
			printf("\nFound product: \n");
			printf("%-20s %-10s\t", "Name", "Barcode");
			printf("%-20s %-10s %s\n", "Type", "Price", "Count In Stoke");
			printf("--------------------------------------------------------------------------------\n");
			printProduct(foundProduct);
		}
		else
			printf("There is no product with that name \n");
		break;
	case eByBarcode:
		foundProduct = searchProductByBarcode(pMarket);
		if (foundProduct != NULL)
		{
			printf("\nFound product: \n");
			printf("%-20s %-10s\t", "Name", "Barcode");
			printf("%-20s %-10s %s\n", "Type", "Price", "Count In Stoke");
			printf("--------------------------------------------------------------------------------\n");
			printProduct(foundProduct);
		}
		else
			printf("There is no product with that barcode \n");
		break;
	case eByType:
		foundProduct = searchProductByType(pMarket);
		if (foundProduct != NULL)
		{
			printf("\nFound product: \n");
			printf("%-20s %-10s\t", "Name", "Barcode");
			printf("%-20s %-10s %s\n", "Type", "Price", "Count In Stoke");
			printf("--------------------------------------------------------------------------------\n");
			printProduct(foundProduct);
		}
		else
			printf("There is no product from that type \n");
		break;
	case eByPrice:
		foundProduct = searchProductByPrice(pMarket);
		if (foundProduct != NULL)
		{
			printf("\nFound product: \n");
			printf("%-20s %-10s\t", "Name", "Barcode");
			printf("%-20s %-10s %s\n", "Type", "Price", "Count In Stoke");
			printf("--------------------------------------------------------------------------------\n");
			printProduct(foundProduct);
		}
		else
			printf("\nThere is no product with that price \n");
		break;
	case eByNothing:
		searchProductByNothing(pMarket);
		break;
	}
}

Product* searchProductByName(SuperMarket* pMarket)						//Search product by name
{
	Product tmpProduct = { "", "", eNofProductType, 0, 0 };
	Product* tmpProductPointer = &tmpProduct;
	printf("\nSearch by name: \n");
	printf("enter product name to search up to %d chars\n", NAME_LENGTH - 1);
	myGets(tmpProduct.name, NAME_LENGTH);
	Product** foundProduct = (Product**)bsearch(&tmpProductPointer, pMarket->productArr, pMarket->productCount, sizeof(Product*), compareProductsByName);
	if (foundProduct != NULL)
		return *foundProduct;
	else
		return NULL;
}

Product* searchProductByBarcode(SuperMarket* pMarket)					//Search product by barcode
{
	Product tmpProduct = { "", "", eNofProductType, 0, 0 };
	Product* tmpProductPointer = &tmpProduct;
	printf("\nSearch by barcode: \n");
	getBorcdeCode(tmpProduct.barcode);
	Product** foundProduct = (Product**)bsearch(&tmpProductPointer, pMarket->productArr, pMarket->productCount, sizeof(Product*), compareProductsByBarcode);
	if (foundProduct != NULL)
		return *foundProduct;
	else
		return NULL;
}

Product* searchProductByType(SuperMarket* pMarket)						//Search product by type (The first one will be found)
{
	Product tmpProduct = { "", "", eNofProductType, 0, 0 };
	Product* tmpProductPointer = &tmpProduct;
	printf("\nSearch by type: \n");
	tmpProduct.type = getProductType();
	Product** foundProduct = (Product**)bsearch(&tmpProductPointer, pMarket->productArr, pMarket->productCount, sizeof(Product*), compareProductsByType);
	if (foundProduct != NULL)
		return *foundProduct;
	else
		return NULL;
}

Product* searchProductByPrice(SuperMarket* pMarket)						//Search product by price
{
	Product tmpProduct = { "", "", eNofProductType, 0, 0 };
	Product* tmpProductPointer = &tmpProduct;
	printf("\nSearch by price: \n");
	printf("Enter product price \t");
	scanf("%f", &tmpProduct.price);
	Product** foundProduct = (Product**)bsearch(&tmpProductPointer, pMarket->productArr, pMarket->productCount, sizeof(Product*), compareProductsByPrice);
	if (foundProduct != NULL)
		return *foundProduct;
	else
		return NULL;
}

void searchProductByNothing(SuperMarket* pMarket)						//Search product by nothing
{
	printf("\nThe array of products is not sorted, you need to sort it first and then do binary search (option 5 in menu) \n");
}

int loadSuperMarket(SuperMarket* pMarket)								//Load super market
{
	if (loadSuperMarketFromFile(pMarket) != LOAD_FROM_FILE)
		if (initSuperMarket(pMarket) != 1)
			return 0;
	return 1;
}

int loadSuperMarketFromFile(SuperMarket* pMarket)						//Load super market from file
{
	FILE* fp;
	int sizeOfString;
	fp = fopen(SUPERMARKET_FILE_NAME, "rb"); //Open super market bin file
	if (!fp) //Failed to open file
		return 0;
	pMarket->name = readStringFromFile(fp); //Read the name of super market
	readIntFromFile(&(pMarket->location.num), fp); //Read the house num of super market
	pMarket->location.street = readStringFromFile(fp); //Read the street name of super market
	pMarket->location.city = readStringFromFile(fp); //Read the city name of super market
	int readValue;
	readIntFromFile(&readValue, fp); //Read the field the products sort by
	pMarket->sortBy = getSortTypeByNum(readValue); //Put the sort by value
	readIntFromFile(&(pMarket->productCount), fp); //Read the number of products in super market
	pMarket->productArr = (Product**)malloc((pMarket->productCount) * sizeof(Product*)); //Make product array
	for (int productNum = 0; productNum < pMarket->productCount; productNum++) //Read all products
	{
		Product* pProd = (Product*)calloc(1, sizeof(Product)); //Make product
		readIntFromFile(&sizeOfString, fp); //Read the length of product name
		readCharsFromFile(pProd->name, sizeOfString, fp); //Read the name of product
		readIntFromFile(&sizeOfString, fp); //Read the length of barcode
		readCharsFromFile(pProd->barcode, sizeOfString, fp); //Read the barcode of product
		readIntFromFile(&readValue, fp); //Read the type of product
		pProd->type = getProductTypeByNum(readValue); //Put the product type value
		readFloatFromFile(&(pProd->price), fp); //Read the price of product
		readIntFromFile(&(pProd->count), fp); //Read the count of product
		*((pMarket->productArr) + productNum) = pProd; //Add the product to product array
	}
	fclose(fp);
	fp = fopen(CUSTOMERS_FILE_NAME, "r"); //Open customers text file
	if (!fp) //Failed to open file
	{
		pMarket->customerCount = 0;
		pMarket->customerArr = NULL;
		return LOAD_FROM_FILE;
	}
	readIntFromFile(&(pMarket->customerCount), fp); //Read number of customers in super market
	pMarket->customerArr = (Customer*)malloc((pMarket->customerCount) * sizeof(Customer)); //Make customers array
	for (int customerNum = 0; customerNum < pMarket->customerCount; customerNum++) //Read all customers
	{
		Customer pCust; //Make customer
		pCust.name = readStringFromFile(fp); //Read customer name
		*((pMarket->customerArr) + customerNum) = pCust; //Add the customer to customers array
	}
	fclose(fp);
	return LOAD_FROM_FILE;
}

void saveSuperMarket(SuperMarket* pMarket)								//Save super market to file
{
	FILE* fp;
	fp = fopen(SUPERMARKET_FILE_NAME, "wb"); //Write to super market bin file
	if (!fp) //Failed to open file
		return;
	writeStringToFile(pMarket->name, fp); //Write super market name
	writeIntToFile(pMarket->location.num, fp); //Write house num
	writeStringToFile(pMarket->location.street, fp); //Write street name
	writeStringToFile(pMarket->location.city, fp); //Write city name
	writeIntToFile(getSortTypeNum(pMarket->sortBy), fp); //Write sort by num
	writeIntToFile(pMarket->productCount, fp); //Write number of products
	for (int productNum = 0; productNum < pMarket->productCount; productNum++) //Write all products
	{
		writeStringToFile((*((pMarket->productArr) + productNum))->name, fp); //Write product name
		writeStringToFile((*((pMarket->productArr) + productNum))->barcode, fp); //Write product barcode
		writeIntToFile(getProductTypeInInt((*((pMarket->productArr) + productNum))->type), fp); //Write product type in int
		writeFloatToFile((*((pMarket->productArr) + productNum))->price, fp); //Write product price
		writeIntToFile((*((pMarket->productArr) + productNum))->count, fp); //Write product count
	}
	fclose(fp);
	fp = fopen(CUSTOMERS_FILE_NAME, "w"); //Write to customers text file
	if (!fp) //Failed to open file
		return;
	writeIntToFile(pMarket->customerCount, fp); //Write number of customers
	for (int customerNum = 0; customerNum < pMarket->customerCount; customerNum++) //Write all customers
		writeStringToFile(((pMarket->customerArr) + customerNum)->name, fp); //Write customer name
	fclose(fp);
}

void generalArrayFunction(void* arr, int numOfElementsInArray, int sizeOfEachElement, void(*f)(void* element))	 //General function to array
{
	if (f == printProductV) //Print all products
	{
		printf("There are %d products \n\n", numOfElementsInArray);
		printf("%-20s %-10s\t", "Name", "Barcode");
		printf("%-20s %-10s %s\n", "Type", "Price", "Count In Stoke");
		printf("--------------------------------------------------------------------------------\n");
		for (int numOfElement = 0; numOfElement < numOfElementsInArray; numOfElement++)
			f((char*)(arr)+numOfElement * sizeOfEachElement);
		return;
	}
	if (f == printCustomerV) //Print all customers
	{
		printf("There are %d listed customers\n", numOfElementsInArray);
		for (int numOfElement = 0; numOfElement < numOfElementsInArray; numOfElement++)
			f((char*)(arr)+numOfElement * sizeOfEachElement);
		return;
	}
	if (f == freeCustomerV) //Free all customers
	{
		for (int numOfElement = 0; numOfElement < numOfElementsInArray; numOfElement++)
			f((char*)(arr)+numOfElement * sizeOfEachElement);
		return;
	}
}
