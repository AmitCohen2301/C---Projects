#pragma once
#include "Address.h"
#include "Customer.h"
#include "Product.h"
#include "ShoppingCart.h"

#define SUPERMARKET_FILE_NAME "SuperMarket.bin"
#define CUSTOMERS_FILE_NAME "Customers.txt"
#define LOAD_FROM_FILE 1

typedef enum { eByName, eByBarcode, eByType, eByPrice, eByNothing, eNofSortType } eSortType;
const char* sortTypeStr[eNofSortType];

typedef struct
{
	char* name;
	Address location;
	Customer* customerArr;
	int customerCount;
	Product** productArr;
	int productCount;
	eSortType sortBy;
}SuperMarket;


int	initSuperMarket(SuperMarket* pMarket);								//Init new supermarket
void printSuperMarket(const SuperMarket* pMarket);						//Print super market
int	addProduct(SuperMarket* pMarket);									//Add product to super market
int	addNewProduct(SuperMarket* pMarket, const char* barcode);			//Add new product to super market
int	addCustomer(SuperMarket* pMarket);									//Add customer to super market
void doShopping(SuperMarket* pMarket);									//Do shopping procedure
void printProductByType(SuperMarket* pMarket);							//Print all product from a specific type
int	getProductIndexByBarcode(SuperMarket* pMarket, const char* barcode);//Get product index by the barcode
Product* getProductByBarcode(SuperMarket* pMarket, const char* barcode);//Get product by the barcode
Product* getProductFromUser(SuperMarket* pMarket, char* barcode);		//Get product from user by barcode
void getUniquBarcode(char* barcode, SuperMarket* pMarket);				//Check the barcode is unique
Customer* FindCustomerByName(SuperMarket* pMarket, const char* name);	//Find customer according to name
Customer* getCustomerWhoShop(SuperMarket* pMarket);						//Get customer from super market
void fillCart(SuperMarket* pMarket, ShoppingCart* pCart);				//Put items in cart
Product* getProductAndCount(SuperMarket* pMarket, int* pCount);			//Get product and count from super market
void freeMarket(SuperMarket* pMarket);									//Free the super market
eSortType getSortType();												//Get sort type from user
eSortType getSortTypeByNum(int numOfSortType);							//Get sort type by number
int getSortTypeNum(eSortType sortType);									//Get sort type num
const char*	getSortTypeStr(eSortType type);								//Get sort type in string
void sortProductsByUser(SuperMarket* pMarket);							//Sort products in super market according to user choice
void sortProductsBy(SuperMarket* pMarket, eSortType typeToSort);		//Sort products in super market by specific type
void binarySearchToProduct(SuperMarket* pMarket);						//Binary search to product according to the sort of super market
Product* searchProductByName(SuperMarket* pMarket);						//Search product by name
Product* searchProductByBarcode(SuperMarket* pMarket);					//Search product by barcode
Product* searchProductByType(SuperMarket* pMarket);						//Search product by type
Product* searchProductByPrice(SuperMarket* pMarket);					//Search product by price
void searchProductByNothing(SuperMarket* pMarket);						//Search product by nothing
int loadSuperMarket(SuperMarket* pMarket);								//Load super market
int loadSuperMarketFromFile(SuperMarket* pMarket);						//Load super market from file
void saveSuperMarket(SuperMarket* pMarket);								//Save super market to file
void generalArrayFunction(void* arr, int numOfElementsInArray, int sizeOfEachElement, void(*f)(void* element));	 //General function to array