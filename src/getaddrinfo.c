/*************************************************************************
    > File Name: getaddrinfo.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Mon 20 Apr 2020 11:31:19 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>

//struct addrinfo addr{
//	int ai_protocol;
//	int ai_family;
//	int ai_socktype;
//}
int main()
{
	struct addrinfo hostaddr;

	getaddrinfo();
}
