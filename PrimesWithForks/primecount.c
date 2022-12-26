#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/mman.h>
#include <getopt.h>
#include <sys/wait.h>

void parseargs(char *argv[], int argc, int *lval, int *uval, int *nval, int *pval); // Parse the flags in the argv into relevant numbers
int isprime(int n);

int main (int argc, char **argv)
{
	int lval = 1; // The lowest number to check if prime
	int uval = 100; // The bigest number to check if prime
	int nval = 10; // How many prime numbers to print
	int pval = 4; // How many process will run
	char *flagarr = NULL; // Arr that resemble if number is prime or no (lval is in index 0 and so on)
	int numToCheckOrPrint; // Number to check if prime (at check stage) or to print (in print stage)
	int counterOfPrimes = 0; // Counter to how many primes there are
	int counterOfProcess; // Counter to process
	int rc; // Return code from process
	int i; // Index

	parseargs(argv, argc, &lval, &uval, &nval, &pval); // Parse arguments
	if (uval < lval) // The upper value is lower than the lower value
	{
		fprintf(stderr, "Upper bound should not be smaller then lower bound\n");
		exit(1);
	}    
	if (lval < 2) // The lower value is lower than two
	{
		lval = 2;
		uval = (uval > 1) ? uval : 1;
	}

	flagarr= (char *)mmap(NULL, sizeof(char) * (uval-lval+1), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); // Allocate flags arr to numbers
	if (flagarr == MAP_FAILED) // Failed to give memory
	{
		fprintf(stderr, "Map error\n");
		exit(1);
	}

	for (counterOfProcess = 0; counterOfProcess < pval; counterOfProcess++) // Make process
	{
		rc = fork();
		if (rc < 0) // Failed to make process
		{
			fprintf(stderr, "Fork error\n");
			exit(1);
		}
		else if (rc == 0) // We are in son
		{
			for (numToCheckOrPrint = lval + counterOfProcess; numToCheckOrPrint <= uval; numToCheckOrPrint += pval) // Set flag arr
			{
				if (isprime(numToCheckOrPrint)) // Num is prime
					flagarr[numToCheckOrPrint - lval] = 1;
				else // Num is not prime
					flagarr[numToCheckOrPrint - lval] = 0; 
			}
			return 1; // End the process of son
		}
	}

	for (counterOfProcess = 0; counterOfProcess < pval; counterOfProcess++) // Wait to all sons to return
		wait(NULL);

	for (i = 0; i < uval; i++) // Count how many primes
		if (flagarr[i])
			counterOfPrimes++;

	printf("Found %d primes%c\n", counterOfPrimes, counterOfPrimes ? ':' : '.'); // Print results
	for (numToCheckOrPrint = lval; (numToCheckOrPrint <= uval) && (nval > 0); numToCheckOrPrint++)
		if (flagarr[numToCheckOrPrint - lval])
		{
			counterOfPrimes--;
			nval--;
			printf("%d%c", numToCheckOrPrint, counterOfPrimes && nval ? ',' : '\n');  
		}

	munmap(flagarr, uval-lval+1); // Release mmap memory
	return 0;
}
 
void parseargs(char *argv[], int argc, int *lval, int *uval, int *nval, int *pval) // Parse the flags in the argv into relevant numbers
{
	int ch;

	opterr = 0;
	while ((ch = getopt (argc, argv, "l:u:n:p:")) != -1) // Move on all argv
	switch (ch) // Check witch flag
	{
		case 'l': // Lower bound flag
			*lval = atoi(optarg);
			break;
		case 'u': // Upper bound flag 
			*uval = atoi(optarg);
			break;
		case 'n': // Number of prime nums to print flag
			*nval = atoi(optarg);
			break;
		case 'p': // Number of process to run flag
			*pval = atoi(optarg);
			break;
		case '?': // Help
			if ((optopt == 'l') || (optopt == 'u') || (optopt == 'n') || (optopt == 'p'))
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
	static int *primes = NULL; 	// NOTE: static !
	static int size = 0;		// NOTE: static !
	static int maxprime;		// NOTE: static !
	int root;
	int i;

	if (primes == NULL) // Init primes array (executed on first call)
	{
		primes = (int *)malloc(2*sizeof(int));
		if (primes == NULL)
			exit(1);
		size = 2;
		primes[0] = 2;
		primes[1] = 3;
		maxprime = 3;
	}

	root = (int)(sqrt(n));

	while (root > maxprime) // Update primes array, if needed
		for (i = maxprime + 2 ;  ; i+=2) // Increase max prime by two (even numbers are not prime)
 			if (isprime(i)) // Check if new num is prime
			{
				size++;
				primes = (int *)realloc(primes, size * sizeof(int)); // Increase size of arr
				if (primes == NULL)
					exit(1);
				primes[size-1] = i;
				maxprime = i;
				break;
			}

	if (n <= 0) // Check n = 0 or less case
		return -1;
	if (n == 1) // Check n = 1 cases
		return 0;

	for (i = 0 ; ((i < size) && (root >= primes[i])) ; i++) // Check if prime
		if ((n % primes[i]) == 0)
			return 0;
	return 1; // Num is prime
}
