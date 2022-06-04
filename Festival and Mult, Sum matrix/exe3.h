#ifndef EXE3_H

//prototypes and defines

#define EXE3_H
#define FIRST_DAY 1
#define LAST_DAY 7
#define NUMBER_TO_STOP 0
#define DAYS_IN_WEEK 7

void resetSoldTickets(int *soldTickets);
int checkValidDay(int dayNum, int firstDay, int lastDAY);
int getDayAndTickets(int *soldTickets, int startDay, int endDay, int *selectedDay, int *numOfBuyTickets);
void findMaxMinArr(int *soldTickets, int lengthOfSoldTickets, int startDay, int lastDay, int *maxDay, int *minDay);
void printMinMax(int *soldTickets, int maxDay, int minDay);
void doTickets();

#endif
