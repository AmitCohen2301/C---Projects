#pragma once


#define LEN 20
#define MAX_PER_TABLE 6

typedef struct
{
	char	familyName[LEN];
	int		personCount;
	int		presentValue;
} Family;

typedef struct
{
	int		personCount;
	int		totalPresents;
} Table;

typedef struct
{
	Family*	familiesArr;
	int		familiesCount;
	Table*	tableArr;
	int		tableCount;
} Wedding;

void runWeddingFunc();																								//Run wedding functions
int		addFamilyToWedding(Wedding* pWed,const Family* pGuest);														//Add family to wedding
Table*	getTable(Wedding* pWed, const Family* pGuest);																//Get table to add family
int		addTableToArr(Wedding* pWed, const Table* pTable);															//Add table to array of tables
const void*	generalGetMax(const void* arr, int (compare)(const void*, const void*), int sizeOfArr, int sizeOfCell);	//General get max family
int		compareFamilyPerPresentPerPerson(const void* f1, const void* f2);											//Compare families by present per person avg
int		addFamilyToArr(Wedding* pWed, const Family* pFamiliy);														//Add family to array of families
void	printWedding(const Wedding* pWed);																			//Print wedding
void	printTables(const Wedding* pWed);																			//Print all tables
void	printTable(const Table* pTable);																			//Print table
void	printFamilies(const Wedding* pWed);																			//Print all families
void	printFamily(const Family* pFam);																			//Print family
void	freeWedding(Wedding* pWed);																					//Free wedding