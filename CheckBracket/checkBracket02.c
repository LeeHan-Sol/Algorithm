#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* substr(char*, int, int);
char* checkBracket(char*);

int main(int argc, char * argv[])
{
    int length = 0;
    char * p = NULL;
    char *w = NULL;

	/*
    memset(buffer, 0x00, sizeof(buffer));
    fgets(buffer, sizeof(buffer), stdin);
    length = strlen(buffer);
    buffer[length - 1] = '\0';
	*/
	p = argv[1];
	printf("%s\n", argv[1]);
	length = strlen(p);

    w = (char*)malloc((sizeof(char) * length));
    memset(w, 0x00, length);
    strcpy(w, p);

    strcpy(w, checkBracket(w));

    printf("%s\n", w);

    return 0;
}

char* substr(char* str, int m, int n)
{
    char * temp = str;
    
    temp = (char*)malloc(sizeof(char) * (n+1));

	for(int i = m; i <= n + m && *(str + i) != 0x00; i++)
		*(temp + i - m) = *(str + i);
	*(temp + n) = 0x00;
    
    return temp;
}

char* checkBracket(char* w)
{
    int left = 0, right = 0, length = 0, flag = 0;
    char *u = NULL, *v = NULL, *temp = NULL;

    length = strlen(w);

    if(!length)
    {
        return w;
    }

    u = (char*)malloc(sizeof(char) * length);
    memset(u, 0x00, length);
    v = (char*)malloc(sizeof(char) * length);
    memset(v, 0x00, length);
    temp = (char*)malloc(sizeof(char*) * length);
    memset(temp, 0x00, length);

    for(int i = 0; i < length; i++)
    {
        strcat(u, substr(w, i, 1));

        if(!strncmp(substr(w, i, 1), "(", 1))
        {
            left++;
        }
        else if(!strncmp(substr(w, i, 1), ")", 1))
        {
            right++;
        }

        if(left < right)
        {
            flag = 1;
        }
        
        if(left == right && left != 0)
        {
            strcat(v, (w + i + 1));
            break;
        }
    }

    if(!flag) 
    {
        strcat(u, checkBracket(v));
        
        return u;
    }
    else 
    {
        strcat(temp, "(");
        strcat(temp, checkBracket(v));
        strcat(temp, ")");

        int lengthOfu = strlen(u);
        char* tempU = (char*)malloc((sizeof(char) * lengthOfu));
        memset(tempU, 0x00, lengthOfu);
        for(int i = 1; i < lengthOfu - 1; i++)
        {
            if(!strcmp("(", substr(u, i, 1)))
            {
                strcat(tempU, ")");
            }
            else if(!strcmp(")", substr(u, i, 1)))
            {
                strcat(tempU, "(");
            }
        }
        strcat(temp, tempU);

        return temp;
    }
}
