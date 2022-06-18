#ifndef FESTIVAL_H

//prototypes and defines

#define FESTIVAL_H
#define FIRST_DAY 1
#define LAST_DAY 7
#define NUMBER_TO_STOP 0
#define DAYS_IN_WEEK 7

void resetSoldTickets(int *soldTickets);																			//Reset the number of sold tickets
int checkValidDay(int dayNum, int firstDay, int lastDAY);															//Check the day is valid
int getDayAndTickets(int *soldTickets, int startDay, int endDay, int *selectedDay, int *numOfBuyTickets);			//Get day and number of tickets
void findMaxMinArr(int *soldTickets, int lengthOfSoldTickets, int startDay, int lastDay, int *maxDay, int *minDay);	//Find the min and max in array
void printMinMax(int *soldTickets, int maxDay, int minDay);															//Print the min and max in arr
void doTickets();																									//Do the ticket procces

#endif