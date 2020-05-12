#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error(char*);
int** alloc2Dim(int**, int, int);
int min(int, int);
int squared(int, int);

int main()
{
    int count = 0, number = 0;
    int **array;
    char buffer[128], strNumber[32];
    FILE *ifp;
    if((ifp = fopen("input.txt", "r")) == NULL)
        error("fopen");

    fgets(buffer, 128, ifp);
    count = atoi(buffer);
    memset(strNumber, 0x00, 32);

    array = alloc2Dim(array, count, 3);

    for(int i = 0; i < count; i++)
    {
        while(!feof(ifp))
        {
            memset(buffer, 0x00, sizeof(buffer));
            fgets(buffer, 2, ifp);

            if(!strcmp(buffer, " ") || !strcmp(buffer, "\n"))
            {
                number = atoi(strNumber); 

                while(1)
                {
                    if((number % 2) == 0)
                    {
                        array[i][0]++;
                        number /= 2;
                    }
                    else if((number % 5) == 0)
                    {
                        array[i][1]++;
                        number /= 5;
                    }
                    else 
                    {
                        if(array[i][2] == 0) 
                        {
                            array[i][2] += (number % 10);
                        }
                        else
                        {
                            array[i][2] *= number % 10;
                        }
                        break;
                    }
                }
                
                memset(strNumber, 0x00, sizeof(strNumber));
                if(!strcmp(buffer, "\n"))
                {
                    break;
                }
            }
            else
            {
                strcat(strNumber, buffer);
                continue;
            }
        }
    }

    for(int i = 0; i < count; i++)
    {
        int minimum = min(array[i][0], array[i][1]);
        int lastNot0 = 0, indexOf2 = 1, indexOf5 = 1;

        if((array[i][0] - minimum) != 0) 
            indexOf2 = squared(2, (array[i][0] - minimum));
        if((array[i][1] - minimum) != 0) 
            indexOf5 = squared(5, (array[i][1] - minimum));

        lastNot0 = indexOf2 * indexOf5 * array[i][2];
        lastNot0 %= 10;

        printf("%d %d\n", lastNot0, minimum);
    }
    
    fclose(ifp);

    for(int i = 0; i < count; i++) free(array[i]);
    free(array);

    return 0;
}

int** alloc2Dim(int** array, int height, int width)
{
    array = (int **)malloc(sizeof(int*) * height);
    if(array == NULL) error("malloc **array");
    for(int i = 0; i < height; i++)
    {
        array[i] = (int *)malloc(sizeof(int) * width);
        for(int j = 0; j < width; j++)
        {
            array[i][j] = 0;
        }
    }

    return array;
}

void error(char *str)
{
    printf("ERROR : %s\n", str);
    exit(1);
}

int min(int a, int b)
{
    return (a <= b) ? a : b;
}

int squared(int a, int b)
{
    int temp = 1;
    for(int i = 0; i < b; i++)
    {
        temp *= a;
    }
    return temp;
}
