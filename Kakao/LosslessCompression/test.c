#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayStr(char *, int);

int main(int argc, char **argv)
{
	int start = 0, end = 0; //부분 문자열 시작, 끝
	int lengthOfsubStr = 0; //부분 문자열 길이
	char c = 0x00;
	
	printf("c : %p\n", &c);
	*((char*)(&c + 1)) = 0x41;
	*((char*)(&c + 2)) = 0x42;
	for(int i = 1; i < 3; i++)
		printf("*(&c + %d) : %c  [%p]\n", i, *(&c + i), (&c + i));
	
	char * str = (char *)malloc(sizeof(char) * 25);
	char * subStr = NULL;

	//문자열을 '\0'로 초기화
	memset(str, 0x00, 25);

	strcpy(str, "abcabcabcabcdededededede");

	printf("str : %s [%p]\n\n", str, str);

	//부분 문자열 "abc" 얻기
	start = 3;
	end = 5;
	lengthOfsubStr = end - start + 1;

	subStr = (char *)malloc(sizeof(char) * (lengthOfsubStr + 1));
	memset(subStr, 0x00, lengthOfsubStr + 1);
	
	for(int i = start; i <= end; i++)
	{
		c = *(str + i);
		strcat(subStr, &c);
	}
	
	/*
	strncpy(subStr, str + start, lengthOfsubStr);
	*(subStr + lengthOfsubStr) = 0x00;
	*/
	printf("subStr : %s [%p]\n", subStr, subStr);

	printf("*(subStr + 6) : %s [%p]\n", (subStr + 6), (subStr + 6));
	return 0;
}

void displayStr(char * str, int length)
{
	for(int i = 0; i < length; i++)
	{
		printf("*(str + i) : %c\n", *(str + i));
	}
}
