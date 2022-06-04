#include <stdio.h>
#include "exe3.h"

void resetSoldTickets(int *soldTickets)
{
	int dayNum;
	for(dayNum = 0; dayNum < DAYS_IN_WEEK; dayNum++)
	{
		*soldTickets = 0;
		soldTickets++;
	}
}

int checkValidDay(int dayNum, int firstDay, int lastDAY)
{
	if((dayNum < firstDay) || (dayNum > lastDAY))
		return 0;
	return 1;
}

int getDayAndTickets(int *soldTickets, int startDay, int endDay, int *selectedDayPointer, int *numOfBuyTickets)
{
	int selectedDay, ticketsCount;
	printf("Enter day (%d to %d) enter %d to stop \n", startDay, endDay, NUMBER_TO_STOP);
	scanf("%d", &selectedDay);
	fflush(stdin);
	while((checkValidDay(selectedDay, startDay, endDay) == 0) && (selectedDay != NUMBER_TO_STOP)) //Check day is ok
	{
		printf("You entered invalid day! \n");
		printf("Enter day (%d to %d) enter %d to stop \n", startDay, endDay, NUMBER_TO_STOP);
		scanf("%d", &selectedDay);
		fflush(stdin);
	}
	if(selectedDay == NUMBER_TO_STOP) //Want to stop
	{
		return 0;
	}
	printf("Enter tickets count \n");
	scanf("%d", &ticketsCount);
	while(ticketsCount < 0) //Check tickets num are valid
	{
		printf("You entered tickets count! \n");
		printf("Enter tickets count \n");
		scanf("%d", &ticketsCount);
		fflush(stdin);
	}
	*selectedDayPointer = selectedDay;
	*numOfBuyTickets = ticketsCount;
	return 1;
}

void findMaxMinArr(int *soldTickets, int lengthOfSoldTickets, int startDay, int lastDay, int *maxDay, int *minDay)
{
	int *pointerInSoldTickets = soldTickets;
	int dayNum, minTickets, maxTickets;
	for(dayNum = 1; dayNum < startDay; dayNum++) //Get to first day
		pointerInSoldTickets++;
	*maxDay = startDay;
	maxTickets = *pointerInSoldTickets;
	*minDay = startDay;
	minTickets = *pointerInSoldTickets;
	for(dayNum = startDay; dayNum <= lastDay; dayNum++) //Move on all relevant days
	{
		if(*pointerInSoldTickets < minTickets) //New min
		{
			*minDay = dayNum;
			minTickets = *pointerInSoldTickets;
		}
		if(*pointerInSoldTickets > maxTickets) //New max
		{
			*maxDay = dayNum;
			maxTickets = *pointerInSoldTickets;
		}
		pointerInSoldTickets++;
	}
}

void printMinMax(int *soldTickets, int maxDay, int minDay)
{
	int numDay;
	int *pointerInsoldTickets = soldTickets;
	for(numDay = 1; numDay < maxDay; numDay++) //Get to max day
		pointerInsoldTickets++;
	printf("The day with max tickets is: %d tickets: %d \n", maxDay, *pointerInsoldTickets);
	pointerInsoldTickets = soldTickets;
	for(numDay = 1; numDay < minDay; numDay++) //Get to min day
		pointerInsoldTickets++;
	printf("The day with min tickets is: %d tickets: %d \n \n", minDay, *pointerInsoldTickets);
}

void doTickets()
{
	int startDay, endDay, numOfBuyTickets, maxDay, minDay, selectedDay;
	int soldTickets[DAYS_IN_WEEK];
	resetSoldTickets((int*)soldTickets);
	printf("\nEnter start day of the festival between %d to %d \n", FIRST_DAY, LAST_DAY);
	scanf("%d", &startDay);
	fflush(stdin);
	while(checkValidDay(startDay, FIRST_DAY, LAST_DAY) == 0) //Check the start day is valid
	{
		printf("You entered invalid start day! \n");
		printf("Enter start day of the festival between %d to %d \n", FIRST_DAY, LAST_DAY);
		scanf("%d", &startDay);
		fflush(stdin);
	}
	printf("Enter end day of the festival between %d to %d \n", startDay, LAST_DAY);
	scanf("%d", &endDay);
	fflush(stdin);
	while(checkValidDay(endDay, startDay, LAST_DAY) == 0) //Check the end day is valid
	{
		printf("You entered invalid end day! \n");
		printf("Enter end day of the festival between %d to %d \n", startDay, LAST_DAY);
		scanf("%d", &endDay);
		fflush(stdin);
	}
	while(getDayAndTickets(soldTickets, startDay, endDay, &selectedDay, &numOfBuyTickets) == 1) //Do the sell
	{
		int *pointerToSelectedDay = soldTickets;
		for(int i = 1; i < selectedDay; i++) //Get to the right cell in sold tickets
			pointerToSelectedDay++;
		*pointerToSelectedDay = (*pointerToSelectedDay) + numOfBuyTickets;
	}
	findMaxMinArr((int*)soldTickets, DAYS_IN_WEEK, startDay, endDay, &maxDay , &minDay); //Get the min and max days
	printMinMax((int*)soldTickets, maxDay, minDay);
}
