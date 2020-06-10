#include <stdio.h>
#include <stdlib.h>

void displayArray(int *, int);
void sort(int *, int);
void swap(int *, int *);

int main()
{
	int n = 0;
	scanf("%d", &n);
	if(1 > n || n > 1000) return 0;

//	int * array = (int *)malloc(sizeof(int) * n);
//	if(array == NULL)
//	{
//		fputs("array fail malloc()\n", stderr);
//		exit(1);
//	}

	int array[n];

	for(int i = 0; i < n; i++)
	{
		scanf("%d", (array + i));
	}

	sort(array, n);
	displayArray(array, n);

	return 0;
}

void displayArray(int * array, int size)
{
	if(array == NULL)
		return ;

//	fputs("array 항목\n", stdout);
	for(int i = 0; i < size; i++)
	{
		fprintf(stdout, "%d\n", *(array + i));
	}
//	fputc('\n', stdout);
	
	return ;
}

void sort(int * array, int size)
{
	for(int i = 0; i < size - 1; i++)
	{
		for(int j = i + 1; j < size; j++)
		{
			if(*(array + i) > *(array + j))
			{
				swap(array + i, array + j);
			}
		}
	}

	return ;
}

void swap(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;

	return ;
}
