#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include "Wedding.h"

void runWeddingFunc()																								//Run wedding functions
{	
	Family arr[] = { {"Cohen",5,1000}, {"Levi",3,1200},{"David",2, 1000},{"Luzon",1,300},
			{"Ripa",6,2000},{"Sinay",2,800},{"Menachem",2,700} };

	Wedding wed = { 0 };

	int size = sizeof (arr)/sizeof(Family);

	for (int i = 0; i < size; i++)
		addFamilyToWedding(&wed, &arr[i]);

	printWedding(&wed);

	//Add call to generalGetMax to find best family

	const void* bestFamily = generalGetMax(wed.familiesArr, compareFamilyPerPresentPerPerson, size, sizeof(Family));

	printf("\n\n-------- The best family\t");

	printFamily((Family*)bestFamily);

	printf("\n");

	freeWedding(&wed);
}

int		addFamilyToWedding(Wedding* pWed, const Family* pFamiliy)													//Add family to wedding
{
	Table* tableToAdd = getTable(pWed, pFamiliy); //Search for free table
	if (tableToAdd == NULL) //No free table
	{
		tableToAdd = (Table*)malloc(sizeof(Table)); //Make new table
		if (tableToAdd == NULL) //Fail to give dyn memory
			return 0;
		tableToAdd->personCount = pFamiliy->personCount; //Put first value to num of persons
		tableToAdd->totalPresents = pFamiliy->presentValue; //Put first value to num of presents
		if (addTableToArr(pWed, tableToAdd) == 0) //Add table and check if failed
		{
			free(tableToAdd);
			return 0;
		}
		return addFamilyToArr(pWed, pFamiliy); //Add family to family array
	}
	tableToAdd->personCount += pFamiliy->personCount; //Update number of persons in table
	tableToAdd->totalPresents += pFamiliy->presentValue; //Update total presents in table
	return addFamilyToArr(pWed, pFamiliy); //Add family to family array
}

Table* getTable(Wedding* pWed, const Family* pFamiliy)																//Get table to add family
{
	for (int tableNum = 0; tableNum < pWed->tableCount; tableNum++) //Move on all tables
	{
		int personInTable = ((pWed->tableArr) + tableNum)->personCount; //Get number of persons in table
		int freePlacesInTable = MAX_PER_TABLE - personInTable; //Calc the free places in table
		if (freePlacesInTable >= pFamiliy->personCount) //Check if there is free space to family
			return (pWed->tableArr) + tableNum;
	}
	return NULL; //Not found table
}

int		addTableToArr(Wedding* pWed, const Table* pTable)															//Add table to array of tables
{
	pWed->tableArr = (Table*)realloc(pWed->tableArr, (pWed->tableCount + 1) * sizeof(Table));
	if (!pWed->tableArr) //Fail to give dyn memory
		return 0;

	pWed->tableArr[pWed->tableCount] = *pTable;
	pWed->tableCount++;
	return 1;
}

const void*	generalGetMax(const void* arr, int (compare)(const void*, const void*), int sizeOfArr, int sizeOfCell)	//General get max family
{
	const void *max = arr;
	for (int numOfCell = 0; numOfCell < sizeOfArr; numOfCell++) //Move on every cell in array
	{
		if (compare((char*)arr + numOfCell * sizeOfCell, max) > 0) //Compare each cell to max
			max = (char*)arr + numOfCell * sizeOfCell;
	}
	return max;
}

int compareFamilyPerPresentPerPerson(const void* f1, const void* f2)												//Compare families by present per person avg
{
	Family* pF1 = (Family*)f1;
	Family* pF2 = (Family*)f2;
	double avgF1 = pF1->presentValue / pF1->personCount; //Calc avg of family 1
	double avgF2 = pF2->presentValue / pF2->personCount; //Calc avg of family 2
	if (avgF1 > avgF2) //Check whos avg is bigger
		return 1;
	return -1;
}

int	addFamilyToArr(Wedding* pWed, const Family* pFamiliy)															//Add family to array of families
{
	pWed->familiesArr = (Family*)realloc(pWed->familiesArr, (pWed->familiesCount + 1) * sizeof(Family));
	if (!pWed->familiesArr)
		return 0;

	pWed->familiesArr[pWed->familiesCount] = *pFamiliy;
	pWed->familiesCount++;
	return 1;
}

void	printWedding(const Wedding* pWed)																			//Print wedding
{
	printFamilies(pWed);
	printTables(pWed);
}

void	printTables(const Wedding* pWed)																			//Print all tables
{
	printf("\n---------- There are %d tables in wedding\n", pWed->tableCount);
	for (int i = 0; i < pWed->tableCount; i++)
	{
		printTable(&pWed->tableArr[i]);
	}
}

void	printTable(const Table* pTable)																				//Print table
{
	printf("Table: %d persons, total present %d\n",pTable->personCount, pTable->totalPresents);
}

void	printFamilies(const Wedding* pWed)																			//Print all families
{
	printf("\n---------- There are %d families in wedding\n", pWed->familiesCount);
	for (int i = 0; i < pWed->familiesCount; i++)
	{
		printFamily(&pWed->familiesArr[i]);
	}
}

void	printFamily(const Family* pFam)																				//Print family
{
	printf("Family: %s %d persons, present %d\n", 
		pFam->familyName, pFam->personCount, pFam->presentValue);
}

void	freeWedding(Wedding* pWed)																					//Free wedding
{
	free(pWed->familiesArr);
	free(pWed->tableArr);
}