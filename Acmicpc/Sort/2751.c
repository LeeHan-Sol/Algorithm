#include <stdio.h>
#include <stdlib.h>

void displayArray(int *, int);
void sort(int *, int, int, int);
void swap(int *, int *);

int main()
{
	int n = 0;
	scanf("%d", &n);
	if(1 > n || n > 1000000) return 0;

	int * array = (int *)malloc(sizeof(int) * n);
	if(array == NULL)
	{
		fputs("array fail malloc()\n", stderr);
		exit(1);
	}

	for(int i = 0; i < n; i++)
	{
		scanf("%d", (array + i));
	}

	sort(array, n, 0, n - 1);
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
//		fprintf(stdout, "%3d", *(array + i));
		fprintf(stdout, "%d\n", *(array + i));
	}
	fputc('\n', stdout);
	
	return ;
}

void sort(int * array, int size, int left, int right)
{	
	if(left >= right) return ;

	int pivot = *(array + left);
	int row = left++;
	int high = right;
//	fprintf(stdout, "pivot, row, high : %d] %d, %d\n\n", pivot, row, high);

	for(; left <= right;)
	{
		if(*(array + left) > pivot && *(array + right) < pivot)
		{
			swap(array + left, array + right);
		}
		
		if(*(array + left) < pivot) left++;
		
		if(*(array + right) > pivot) right--;
	}

	swap(array + right, array + row);
//	displayArray(array, size);
//	fprintf(stdout, "left, right : %d, %d\n", left, right);

	sort(array, size, row, right - 1);
	sort(array, size, left, high);

	return ;
}

void swap(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;

	return ;
}
