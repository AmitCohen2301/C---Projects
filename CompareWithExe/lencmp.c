#include <stdio.h>
#include <string.h>

// According to length
int lencmp(const char *str1, const char *str2)
{
	int len1, len2;

	len1 = strlen(str1);
	len2 = strlen(str2);
	if (len1 < len2)
		return 1;
	if (len1 > len2)
		return 2;
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		return -1;
	}
	return lencmp(argv[1], argv[2]);
}
