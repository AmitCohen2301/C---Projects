#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define LINELEN (80)
#define SIZE_TO_READ_FROM_PIPE (1)

char *mygets(char *buf, int len);
int mygeti();

int main(int argc, char *argv[])
{
	char *cmpstr[] = {"lexcmp", "lencmp"};
	int veclen = sizeof(cmpstr)/sizeof(char *);
	char str1[LINELEN + 1]; // First string
	char str2[LINELEN + 1]; // Second string
	int index;
	char returnAns, buf;

	int pfd1[2]; // Var to pipe to write to lexcmp
	int pfd2[2]; // Var to pipe to read from lexcmp
	int pfd3[2]; // Var to pipe to write to lencmp
	int pfd4[2]; // Var to pipe to read from lencmp
	
	if(pipe(pfd1) == -1 || pipe(pfd2) == -1 || pipe(pfd3) == -1 || pipe(pfd4) == -1) // Failed to make pipes
	{
		printf("pipe error");
		return -2;
	}
	
	pid_t lexProg; // Pid for lex prog
	pid_t lenProg; // Pid for len prog

	lexProg = fork(); // Make son (lexcmp)
	
	if(lexProg < -1) // Failed to make son (lexcmp)
	{
		printf("fork error");
		return -2;
	}
	else if(lexProg == 0) // We are in son (lexcmp)
	{
		char *myProgram[] = {"./loopcmp", cmpstr[0], NULL};

        	if(close(pfd1[1]) == -1) // Close the option to write to pipe to write to lexcmp
			return -2;
        	if (pfd1[0] != STDIN_FILENO) // Check if not read from pipe to write to lexcmp
		{
			if(dup2(pfd1[0], STDIN_FILENO) == -1) // Change the standard input to pipe to write to lexcmp
				return -2;
			if (close(pfd1[0]) == -1) // Close the option to read from pipe to write to lexcmp (still can in stdin)
				return -2;
		}
        	if(close(pfd2[0]) == -1) // Close the option to read from pipe to read from lexcmp
			return -2;
        	if (pfd2[1] != STDOUT_FILENO) // Check if not write to pipe to read from lexcmp
		{
			if(dup2(pfd2[1], STDOUT_FILENO) == -1) // Change the standard output to pipe to read from lexcmp
				return -2;
			if (close(pfd2[1]) == -1) // Close the option to write to pipe to read from lexcmp (still can in stdout)
				return -2;
		}
		execve(myProgram[0], myProgram, NULL); // Run the prog that responsible of lex cmp
		return -2;
	}
	else // We are in father (nicecmp)
		lenProg = fork(); // Make son (lencmp)
	
	if(lenProg < -1) // Failed to make son (lencmp)
	{
		printf("fork error");
		return -2;
	}
	else if(lenProg == 0) // We are in son (lencmp)
	{
		char *myProgram[] = {"./loopcmp", cmpstr[1], NULL};
	
		if(close(pfd3[1]) == -1) // Close the option to write to pipe to write to lencmp
			return -2;
	        if (pfd3[0] != STDIN_FILENO) // Check if not read from pipe to write to lencmp
		{
			if(dup2(pfd3[0], STDIN_FILENO) == -1) // Change the standard input to pipe to write to lencmp
				return -2;
			if (close(pfd3[0]) == -1) // Close the option to read from pipe to write to lencmp (still can in stdin)
				return -2;
		}
		if(close(pfd4[0]) == -1) return -2; // Close the option to read from pipe to write to lencmp
        	if (pfd4[1] != STDOUT_FILENO) // Check if not write to pipe to write to lencmp
		{
			if(dup2(pfd4[1], STDOUT_FILENO) == -1) // Change the standard output to pipe to read from lencmp
				return -2;
			if (close(pfd4[1]) == -1) // Close the option to write to pipe to read from lencmp (still can in stdout)
				return -2;
		}
		execve(myProgram[0], myProgram, NULL); // Run the prog that responsible of len cmp
		return -2;
	}

	else // We are in father (nicecmp)
	{
		if(close(pfd1[0]) == -1) // Close the option to read from pipe to write to lexcmp
			return -2;
		if(close(pfd2[1]) == -1) // Close the option to write to pipe to read from lexcmp
			return -2;
		if(close(pfd3[0]) == -1) // Close the option to read from pipe to write to lencmp
			return -2;
		if(close(pfd4[1]) == -1) // Close the option to write to pipe to read from lencmp
			return -2;
		while (1)
		{
			printf("Please enter first string:\n");
			if (mygets(str1, LINELEN) == NULL) // Get first str
				break;
			printf("Please enter second string:\n");
			if (mygets(str2, LINELEN) == NULL) // Get second str
				break;

			char* combineStr;
			combineStr = (char*)(malloc((3 + strlen(str1) + strlen(str2)) * sizeof(char))); // Put two strings in one
			strcpy(combineStr, str1);
			strcat(combineStr,"\n");
			strcat(combineStr, str2);
			strcat(combineStr,"\n");
		
			do { // Print the options to compare
				printf("Please choose:\n");
				for (int i = 0 ; i < veclen ; i++)
					printf("%d - %s\n", i, cmpstr[i]);
				index = mygeti(); // Get chosen compare index
			} while ((index < 0) || (index >= veclen));
			fflush(stdout);
		
			if (index == 0) // Compare by lex
			{
				if(write(pfd1[1], combineStr, strlen(combineStr)) == -1) // Write the strings to pipe to write to lexcmp
					return -2; 
				if(read(pfd2[0], &returnAns, SIZE_TO_READ_FROM_PIPE) == -1) // Read from pipe to read from lexcmp
					return -2;
				if(read(pfd2[0], &buf, SIZE_TO_READ_FROM_PIPE) == -1) // Read buf from pipe to read from lexcmp
					return -2;
			}
			else if (index == 1) // Compare by len
			{
				if(write(pfd3[1], combineStr, strlen(combineStr)) == -1) // Write the strings to pipe to write to lencmp
					return -2;
				if(read(pfd4[0], &returnAns, SIZE_TO_READ_FROM_PIPE) == -1) // Read from pipe to read from lencmp
					return -2;
				if(read(pfd4[0], &buf, SIZE_TO_READ_FROM_PIPE) == -1) // Read buf from pipe to read from lencmp
					return -2;
			}
			printf("%s(%s, %s) == %c\n", cmpstr[index], str1, str2, returnAns);
			fflush(stdout);
			free(combineStr);
		}
		if(close(pfd1[1]) == -1) // Close the write option to pipe to write to lexcmp
			return -2;
		if(close(pfd2[0]) == -1) // Close the read option to pipe to read to lexcmp
			return -2;
		if(close(pfd3[1]) == -1) // Close the write option to pipe to write to lencmp
			return -2;
		if(close(pfd4[0]) == -1) // Close the read option to pipe to read to lencmp
			return -2;

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
	else if (retval) 
		while (getchar() != '\n'); /* get to eol */

	return retval;
}

int mygeti()
{
	int ch;
	int retval=0;

	while(isspace(ch=getchar()));
	while(isdigit(ch))
	{
		retval = retval * 10 + ch - '0';
		ch = getchar();
	}
	while (ch != '\n')
		ch = getchar();
	return retval;
}


