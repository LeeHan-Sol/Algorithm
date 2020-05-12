#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** alloc2Dim(int**, int, int);
int** init2Dim(int**, int, int);
void dup2Dim(int**, int**, int, int);
void clockwise(int**, int, int);
void print2Dim(int**, int, int);

int isOpen(int**, int, int, int);

int main(int argc, char * argv[])
{
    //const int KEY[3][3] = {{0,0,0},{1,0,0},{0,1,1}};
    //const int KEY[3][3] = {{0,0,1},{0,1,0},{1,1,1}};
    const int KEY[3][3] = {{1,0,1},{0,1,1},{1,0,1}};
    const int LOCK[3][3] = {{1,1,1},{1,1,0},{1,0,1}};

    const unsigned int N = sizeof LOCK / sizeof LOCK[0];
    const unsigned int M = sizeof KEY / sizeof KEY[0];
    const unsigned int L = M + (2 * N ) - 2;

    int ** check = alloc2Dim(check, L, L);
    int ** temp = alloc2Dim(temp, L, L);

    int ** clockwiseKey = alloc2Dim(clockwiseKey, M, M);

    int flag = 0;

    for(int i = M - 1; i < L - M + 1; i++)
    {
        for(int j = M - 1; j < L - M + 1; j++)
        {
            check[i][j] = LOCK[i - M + 1][j - M + 1];
        }
    }

    print2Dim(check, L, L);

    //dup2Dim(clockwiseKey, KEY, M, M);
    for(int i = 0; i < M; i++)
        for(int j = 0; j < M; j++)
        {
            clockwiseKey[i][j] = KEY[i][j];
        }

    for(int degree = 0; degree < 4; degree++)
    {
        clockwise(clockwiseKey, M, M);

        printf("(I) KEY\n");
        print2Dim(clockwiseKey, M, M);
        printf("\n\n");

    	for(int i = 0; i < L - M + 1; i++)
    	{
	        for(int j = 0; j < L - M + 1; j++)
	        {
	            dup2Dim(temp, check, L, L);
	            for(int x = 0; x < M; x++)
	            {
		            for(int y = 0; y < M; y++)
		            {
		                temp[i+x][j+y] += clockwiseKey[x][y];
		            }
	            }

	            printf("(I) temp\n");
	            print2Dim(temp, L, L);
    
	            if(isOpen(temp, L, L, M)) 
	            {
		            flag = 1;
		            break;
	            }
	            init2Dim(temp, L, L);
	        }
	        if(flag == 1)
	        {
	            break;
	        }
        }
        if(flag == 1) break;
    }

    if(flag == 1) printf("true\n");
    else printf("false\n");

    return 0;
}

int** alloc2Dim(int** arr, int width, int height)
{
    arr = (int**)malloc(sizeof(int*) * height);

    for(int i = 0; i < height; i++)
        arr[i] = (int*)malloc(sizeof(int) * width);

    return arr;
}

int** init2Dim(int** arr, int width, int height)
{
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            arr[i][j] = 0;
        }
    }

    return arr;
}

void dup2Dim(int** temp, int** arr, int width, int height)
{
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            temp[i][j] = arr[i][j];
        }
    }
}

void clockwise(int ** arr, int width, int height)
{
    int ** temp = alloc2Dim(temp, width, height);

    dup2Dim(temp, arr, width, height);

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            arr[j][2-i] = temp[i][j];
        }
    }
}

void print2Dim(int** arr, int width, int height)
{
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            printf("%4d", arr[i][j]);
        }
        printf("\n");
    }
}

int isOpen(int** arr, int width, int height, int M)
{
    int flag = 1;

    for(int i = M - 1; i < width - M + 1; i++)
    {
        for(int j = M - 1; j < height - M + 1; j++)
        {
            if(arr[i][j] != 1) flag = 0; 
        }
    }

    return flag;
}
