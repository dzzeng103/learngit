/*************************************************************************
    > File Name: structtest.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Mon 18 May 2020 07:46:10 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<string.h>

typedef struct test{
	char e[64];
}TEST;
typedef struct st{
	int a;
	int *c;
	//TEST d;

}ST_TEST;

int main()
{
	ST_TEST a;
	printf("sizeof:%d\n", sizeof(ST_TEST));
	
}
