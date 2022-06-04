#pragma once

#include "ShoppingItem.h"
#include "list.h"

typedef struct
{
	LIST* listOfItems;
}ShoppingCart;

void initCart(ShoppingCart* pCart);													//Init new cart
float getTotalPrice(const ShoppingCart* pCart);										//Get total price of cart
ShoppingItem* getItemByName(ShoppingCart* pCart, const char* name);					//Get item by name
int addItemToCart(ShoppingCart* pCart, const char* name, float price, int count);	//Add item to cart
void printShoppingCart(const ShoppingCart* pCart);									//Print shopping cart
void freeShoppingCart(ShoppingCart* pCart);											//Free shopping cart