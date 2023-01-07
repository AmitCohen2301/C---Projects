#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/mman.h>
#include <getopt.h>
#include <pthread.h>

#define LVAL_DEFAULT 1
#define UVAL_DEFAULT 100
#define NVAL_DEFAULT 10
#define TVAL_DEFAULT 4

void parseargs(char *argv[], int argc, int *lval, int *uval, int *nval, int *tval); // Parse the flags in the argv into relevant numbers
int isprime(int n); // Check if n is prime
void* catchAndCheckPrime(void* args); // Catch and check if number is prime

int catchNumToCheck; // Number to catch and check if prime
pthread_mutex_t catchNumLock; // Lock to catch number in order to check if prime

typedef struct Args // Args parameters
{
	int lval; // The lowest number to check if prime
	int uval; // The bigest number to check if prime
	int nval; // How many prime numbers to print
	int tval; // How many threads to run
	char *flagArr; // Arr that resemble if number is prime or no (lval is in index 0 and so on)
} Args;

int main (int argc, char **argv)
{
	Args args; // All parameters in argv and flag arr to numbers
	args.lval = LVAL_DEFAULT; // Default
	args.uval = UVAL_DEFAULT; // Default
	args.nval = NVAL_DEFAULT; // Default
	args.tval = TVAL_DEFAULT; // Default
	args.flagArr = NULL; // Default
	int counterOfPrimes = 0; // Counter to how many primes there are
	int counterOfThreads; // Counter to threads
	pthread_t *threadArr = NULL; // Arr of all threads
	int numToPrint; // Number to print
	int i; // Index

	parseargs(argv, argc, &(args.lval), &(args.uval), &(args.nval), &(args.tval)); // Parse arguments
	if (args.uval < args.lval) // The upper value is lower than the lower value
	{
		fprintf(stderr, "Upper bound should not be smaller then lower bound\n");
		exit(1);
	}
	if (args.lval < 2) // The lower value is lower than two
	{
		args.lval = 2;
		args.uval = (args.uval > 1) ? args.uval : 1;
	}

	catchNumToCheck = args.lval; // Intilizer the min num to catch to lval

	args.flagArr= (char*)malloc(sizeof(char) * (args.uval - args.lval + 1)); // Allocate flags arr to numbers
	if (args.flagArr == NULL) // Failed to give memory
	{
		fprintf(stderr, "Failed to give memory to flag arr\n");
		exit(1);
	}

	if (pthread_mutex_init(&catchNumLock, NULL) != 0) // Init the lock of catch number
	{
		fprintf(stderr, "Failed to initialize the lock of catch num\n");
		exit(1);
	}

	threadArr = (pthread_t *)malloc(sizeof(pthread_t) * args.tval); // Allocate threads arr
	if (threadArr == NULL) // Failed to give memory
	{
		fprintf(stderr, "Failed to give memory to thread arr\n");
		exit(1);
	}

	for (counterOfThreads = 0; counterOfThreads < args.tval; counterOfThreads++) // Make threads
		if(pthread_create(&threadArr[counterOfThreads], NULL, catchAndCheckPrime, (void*)&args) != 0)
		{
			fprintf(stderr, "Failed to create thread\n");
			exit(1);
		}

	for (counterOfThreads = 0; counterOfThreads < args.tval; counterOfThreads++) // Join all the threads
		if(pthread_join(threadArr[counterOfThreads], NULL) != 0)
		{
			fprintf(stderr, "Failed to join thread\n");
			exit(1);
		}

	for (i = 0; i <= args.uval - args.lval; i++) // Count the number of primes
	{
		if (args.flagArr[i] == 1)
			counterOfPrimes++;
	}

	printf("Found %d primes%c\n", counterOfPrimes, counterOfPrimes ? ':' : '.'); // Print results
	for (numToPrint = args.lval; (numToPrint <= args.uval) && (args.nval > 0); numToPrint++)
		if (args.flagArr[numToPrint - args.lval])
		{
			counterOfPrimes--;
			args.nval--;
			printf("%d%c", numToPrint, counterOfPrimes && args.nval ? ',' : '\n');  
		}
	pthread_mutex_destroy(&catchNumLock);
	free(threadArr);
	free(args.flagArr);
	return 0;
}

void parseargs(char *argv[], int argc, int *lval, int *uval, int *nval, int *tval) // Parse the flags in the argv into relevant numbers
{
	int ch;

	opterr = 0;
	while ((ch = getopt (argc, argv, "l:u:n:t:")) != -1) // Move on all argv
	switch (ch) // Check witch flag
	{
		case 'l':  // Lower bound flag
			*lval = atoi(optarg);
			break;
		case 'u':  // Upper bound flag 
			*uval = atoi(optarg);
			break;
		case 'n': // Number of prime nums to print flag
			*nval = atoi(optarg);
			break;
		case 't': // Number of threads to run flag
			*tval = atoi(optarg);
			break;
		case '?': // Help
			if ((optopt == 'l') || (optopt == 'u') || (optopt == 'n') || (optopt == 't'))
				fprintf (stderr, "Option -%c requires an argument.\n", optopt);
			else if (isprint (optopt))
				fprintf (stderr, "Unknown option `-%c'.\n", optopt);
			else
				fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
			exit(1);
		default:
			exit(1);
	}    
}

int isprime(int n)
{
	int i, root;
	
	if((n != 2) && (n % 2 == 0))
		return 0;
	
	root = (int)(sqrt(n));
	
	for(i = 3; i <= root; i += 2)
		if(n % i == 0)
			return 0;
	
	return 1;
}

void* catchAndCheckPrime(void* args) // Catch and check if number is prime
{
	Args* pArgs;
	int myNumToCheck;

	if(args != NULL) // Parse the pointer
		pArgs = (Args*)args;
	else
	{
		fprintf(stderr, "Must send args to catch\n");
		exit(1);
	}

	while(catchNumToCheck <= pArgs->uval) // Do while there is number to check
	{
		pthread_mutex_lock(&catchNumLock); // Want to catch number
		myNumToCheck = catchNumToCheck;
		catchNumToCheck++;
		pthread_mutex_unlock(&catchNumLock); // Done to catch number
		*((pArgs->flagArr) + myNumToCheck - pArgs->lval) = isprime(myNumToCheck); // Update the flag array
	}
	return NULL;
}
