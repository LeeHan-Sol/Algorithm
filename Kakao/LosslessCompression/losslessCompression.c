#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int length = 0, count = 1, min = 1000, split = 0;
    char buffer[1001];
    memset(buffer, 0x00, sizeof(buffer));

    char *currentUnit, *nextUnit, *result, *minResult, *countStr;

    fgets(buffer, sizeof(buffer), stdin);
    buffer[strlen(buffer) - 1] = 0x00;
    length = strlen(buffer);

    result = malloc(sizeof(char) * length);
    minResult = malloc(sizeof(char) * length);
    countStr = malloc(sizeof(char) * 5);

    for(int i = 1; i < (length / 2) + 1; i++)
    {
        currentUnit = malloc(sizeof(char) * (i+1));
        nextUnit = malloc(sizeof(char) * (i+1));
        memset(&result[0], 0x00, i);

        for(int j = 0; j < length; j+=i)
        {
            strcat(nextUnit, &buffer[j]);
            split = i;
            if((j + i) >= length) split = length - j;
            nextUnit[split] = 0x00;

            if(j == 0)
            {
                strcat(currentUnit, nextUnit);
            }
            
            if(!strcmp(currentUnit, nextUnit) && j != 0)
            {
                count++;
                if((j+i) >= length)
                {
                    memset(&countStr[0], 0x00, 5);
                    sprintf(countStr, "%d", count);
                    strcat(result, countStr);
                    strcat(result, nextUnit);
                    count = 1;
                }
            }
            else if(strcmp(currentUnit, nextUnit))
            {
                if(count > 1)
                {
                    countStr[0] = 0x00;
                    sprintf(countStr, "%d", count);
                    strcat(result, countStr);
                }
                strcat(result, currentUnit);
                if((j+i) >= length)
                {
                    strcat(result, nextUnit);
                }
                count = 1;
            }

            strcpy(currentUnit, nextUnit);
            memset(&nextUnit[0], 0x00, i);
        }
        if(min > strlen(result)) 
        {
            min = strlen(result);
            strcpy(minResult, result);
        }
        memset(&currentUnit[0], 0x00, i);
    }
    printf("%s, %d\n", minResult, min);
    return 0;
}
