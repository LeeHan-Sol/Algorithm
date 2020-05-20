#include <stdio.h>
#include <stdlib.h>

int main()
{
    int ** arr;
    int ** temp;

    arr = (int**)malloc(sizeof(int*) * 3);
    for(int i = 0; i < 3; i++)
        arr[i] = (int*)malloc(sizeof(int) * 3);

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            arr[i][j] = 0;

    temp = arr;


    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            printf("%4d", temp[i][j]);
        }
        printf("\n");
    }

    return 0;
}
