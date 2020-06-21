#include <stdio.h>
#include <stdlib.h>

int main()
{
	int a = 0, b = 0, c = 0;

	scanf("%d %d %d", &a, &b, &c);
	if(0 > a && a > 2100000000) return 0;
	if(0 > b && b > 2100000000) return 0;
	if(0 > c && c > 2100000000) return 0;

	int sub = c - b;

	if(sub <= 0)
	{
		fprintf(stdout, "-1");
		return 0;
	}

	for(int i = 1; ;)
	{
		if(a < sub * i)
		{
			fprintf(stdout, "%d", i);
			break;
		}
		else
		{
			i = a / (sub * i);
			i++;
		}
//		fprintf(stdout, "i : %d\n", i);
	}

	return 0;
}
