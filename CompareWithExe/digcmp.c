#include <stdio.h>
#include <string.h>

// According to number of digits
int digcmp(const char *str1, const char *str2)
{
	int digitsIn1 = 0, digitsIn2 = 0;

	for(int i = 0; i < strlen(str2); i++) //Count digits in 1
	{
		if(str1[i] >= '0' && str1[i] <= '9')
			digitsIn1++;
	}
	for(int i = 0; i < strlen(str2); i++) //Count digits in 2
	{
		if(str2[i] >= '0' && str2[i] <= '9')
			digitsIn2++;
	}
	if (digitsIn1 > digitsIn2)
		return 1;
	if (digitsIn1 < digitsIn2)
		return 2;
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		return -1;
	}
	return digcmp(argv[1], argv[2]);
}
