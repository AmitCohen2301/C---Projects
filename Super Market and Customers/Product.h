#pragma once

typedef enum { eFruitVegtable, eFridge, eFrozen, eShelf, eNofProductType } eProductType;
const char* typeStr[eNofProductType];

#define NAME_LENGTH 20
#define BARCODE_LENGTH 7

typedef struct
{
	char name[NAME_LENGTH + 1];
	char barcode[BARCODE_LENGTH + 1];
	eProductType type;
	float price;
	int	count;
}Product;

void initProduct(Product* pProduct);										//Init new product
void initProductNoBarcode(Product* pProduct);								//Init new product without barcode
void initProductName(Product* pProduct);									//Init product name
void printProduct(const Product* pProduct);									//Print the product
void printProductV(const void* val);										//Print product by casting
void getBorcdeCode(char* code);												//Check barcode is ok and if not ask from user new one
int	isProduct(const Product* pProduct, const char* barcode);					//Check if the barcode is the barcode of the product
eProductType getProductType();												//Get product type from user
eProductType getProductTypeByNum(int num);									//Get product type by num
int getProductTypeInInt(eProductType productType);							//Get product type in int
const char*	getProductTypeStr(eProductType type);							//Get product type in string
void updateProductCount(Product* pProduct);									//Update product count
void freeProduct(Product* pProduct);										//Free product
int compareProductsByName(const void* pProduct1, const void* pProduct2);	//Compare products by name
int compareProductsByBarcode(const void* pProduct1, const void* pProduct2);	//Compare products by barcode
int compareProductsByType(const void* pProduct1, const void* pProduct2);	//Compare products by type
int compareProductsByPrice(const void* pProduct1, const void* pProduct2);	//Compare products by price