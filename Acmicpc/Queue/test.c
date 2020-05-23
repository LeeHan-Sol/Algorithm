#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int integer = 0;

	fgets(integer, sizeof(int) * 1, stdin);

	fprintf(stdout, "%d\n", integer);

	return 0;
}
