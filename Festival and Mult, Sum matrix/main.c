#include <stdio.h>
#include "Mult.h"
#include "Sum.h"
#include "Festival.h"

void showMenu();

int main()
{
	char choiceOption;
	do
	{
		showMenu();
		scanf("%c", &choiceOption);
		while (choiceOption == '\n')
			scanf("%c", &choiceOption);
		fflush(stdin);
		switch (choiceOption)
		{
		case 'A':
		case 'a':
			doSumMat();
			break;
		case 'M':
		case 'm':
			doMultMat();
			break;
		case 'T':
		case 't':
			doTickets();
			break;
		case 'E':
		case 'e':
			printf("\nBye bye have a good day! \n\n");
			break;
		default:
			printf("You entered invalid option! \n");
			break;
		}
	} while ((choiceOption != 'E') && (choiceOption != 'e'));
	return 0;
}

void showMenu()
{
	printf("Please choose one of the following options \n");
	printf("A/a - add two matrices \n");
	printf("M/m - multiply two matrices \n");
	printf("T/t - buy tickets \n");
	printf("E/e - exit \n");
}