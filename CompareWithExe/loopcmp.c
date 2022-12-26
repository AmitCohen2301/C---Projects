#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define LINELEN (80)

char *mygets(char *buf, int len);

int main(int argc, char *argv[])
{
	if (argc != 2) // Not proper main input
		return -1;

	char str1[LINELEN + 1];
	char str2[LINELEN + 1];
	int rc, returnNum;

	while(1) {
		if (mygets(str1, LINELEN) == NULL) // Get first string
			break;
		if (mygets(str2, LINELEN) == NULL) // Get second string
			break;
		
		rc = fork();
		if (rc < 0) // Fork failed
			exit(1);
		else if (rc == 0) { // Child (new process)
			char *myargs[4];
			char *prog = (char*)malloc(sizeof(char) * (strlen(argv[1]) + 3));
			prog = strcat(prog, "./");
			strcat(prog, argv[1]);
			myargs[0] = strdup(prog); // cmp program
			myargs[1] = strdup(str1); // copy first string
			myargs[2] = strdup(str2); // copy second string
			myargs[3] = NULL; // marks end of array
			execvp(myargs[0], myargs); // runs cmp program
			return -2;
		} else { // Father (main)
			wait(&returnNum); // Wait and save return number from child program
		}
		printf("%d \n", WEXITSTATUS(returnNum)); //Print the return number from child program
	}
	return 0;
}

char *mygets(char *buf, int len)
{
	char *retval;

	retval = fgets(buf, len, stdin);
	buf[len] = '\0';
	if (buf[strlen(buf) - 1] == 10) /* trim \r */
		buf[strlen(buf) - 1] = '\0';
	else if (retval) while (getchar() != '\n'); /* get to eol */

	return retval;
}
