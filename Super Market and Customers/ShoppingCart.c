#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ShoppingCart.h"

void initCart(ShoppingCart* pCart)													//Init new cart
{
	pCart->listOfItems = NULL;
}

float getTotalPrice(const ShoppingCart* pCart)										//Get total price of cart
{
	float price = 0;
	if (pCart->listOfItems == NULL) //Empty list of items
		return 0;
	NODE* pItem = pCart->listOfItems->head.next;
	while (pItem != NULL)
	{
		ShoppingItem* itemToCalc = (ShoppingItem*)pItem->key;
		price += (itemToCalc->price) * (itemToCalc->count);
		pItem = pItem->next;
	}
	return price;
}

int	addItemToCart(ShoppingCart* pCart, const char* name, float price, int count)	//Add item to cart
{
	ShoppingItem* pItem = getItemByName(pCart, name);
	if (pItem == NULL) //new item to add
	{
		pItem = createItem(name, price, count);
		if (!pItem)
			return 0;
		if (pCart->listOfItems == NULL) //List is empty
		{
			pCart->listOfItems = (LIST*)malloc(sizeof(LIST));
			L_init(pCart->listOfItems);
			L_insert(&(pCart->listOfItems->head), pItem);
			return 1;
		}
		else //List is not empty
		{
			NODE* nodeBefore = &(pCart->listOfItems->head);
			NODE* nodeToCheck = pCart->listOfItems->head.next;
			while (nodeToCheck != NULL) //Check where to put the new item
			{
				if (strcmp(((ShoppingItem*)nodeToCheck->key)->name, pItem->name) > 0) //Found the place to add
					break;
				nodeBefore = nodeToCheck;
				nodeToCheck = nodeToCheck->next;
			}
			L_insert(nodeBefore, pItem);
			return 1;
		}
	}
	else { //Exist item
		pItem->count += count;
	}
	return 1;
}

void printShoppingCart(const ShoppingCart* pCart)									//Print shopping cart
{
	if (pCart->listOfItems == NULL) //Empty cart
	{
		printf("The cart is empty\n");
		printf("Total bill to pay: 0\n");
		return;
	}
	NODE* tmp = pCart->listOfItems->head.next;
	while (tmp != NULL)
	{
		printItem((ShoppingItem*)(tmp->key));
		tmp = tmp->next;
	}
	printf("Total bill to pay: %.2f\n", getTotalPrice(pCart));
}

ShoppingItem* getItemByName(ShoppingCart* pCart, const char* name)					//Get item by name
{
	if (pCart->listOfItems == NULL) //Empty list of items
		return NULL;
	NODE* pItem = pCart->listOfItems->head.next;
	while (pItem != NULL)
	{
		ShoppingItem* itemToCheck = (ShoppingItem*)pItem->key;
		if (strcmp(itemToCheck->name, name) == 0)
			return itemToCheck;
		pItem = pItem->next;
	}
	return NULL;
}

void freeShoppingCart(ShoppingCart* pCart)											//Free shopping cart
{
	L_free(pCart->listOfItems);
	free(pCart->listOfItems);
}