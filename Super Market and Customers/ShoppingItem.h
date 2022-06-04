#pragma once

typedef struct
{
	char* name;
	float price;
	int	count;
}ShoppingItem;

void printItem(const ShoppingItem* pItem);							//Print item
ShoppingItem* createItem(const char* name, float price, int count);	//Create new item
void freeItem(ShoppingItem* pItem);									//Free item
