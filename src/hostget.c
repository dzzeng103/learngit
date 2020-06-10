/*************************************************************************
    > File Name: hostget.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Mon 20 Apr 2020 07:36:34 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<netdb.h>

/*
 *struct hostent{
	char *h_name;
	char *h_aliases;
	int h_addrtype;
	int h_length;
	char **h_addr_list;
 }
#define h_addr h_addr_list[0]
 *
 *
 * */
int main(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("argc is absent\n");
		exit(1);
	}

	struct hostent *pst;
	pst = gethostbyname(argv[1]);
	if(pst == NULL)
	{
		printf("get error\n");
		exit(1);
	}

	printf("name:%s\n",pst->h_name);
	printf("type:%s\n", pst->h_addrtype == AF_INET ? "IPV4":"IPV6");
	char ip[16];
	inet_ntop(pst->h_addrtype, pst->h_addr_list[0], ip, sizeof(ip));
	printf("ip:%s\n", ip);

	int i = 0;
	while(pst->h_aliases[i] != NULL)
	{
		printf("h_aliases:%s\n", pst->h_aliases[i]);
		i++;
	}

}
