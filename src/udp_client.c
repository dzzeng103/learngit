/*************************************************************************
    > File Name: udp_client.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Mon 20 Apr 2020 04:34:10 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<memory.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/types.h>
#include<netdb.h>

int sockfd;

int main(int argc, char **argv)
{
	if(argc < 3)
	{
		printf("error\n");
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	struct sockaddr_in clientaddr;
	char ip[16];
	char buff[] = "hello world";
	int len = sizeof(buff);
	struct hostent *pst;

	memset(&clientaddr, 0, sizeof(clientaddr));
	clientaddr.sin_family = AF_INET;
	clientaddr.sin_port = htons(atoi(argv[2]));
	pst = gethostbyname(argv[1]);
	if(pst != NULL)
	{
		inet_pton(AF_INET, pst->h_addr_list[0], 
						&clientaddr.sin_addr.s_addr);
	}
	else
	{
		inet_pton(AF_INET, argv[1], &clientaddr.sin_addr.s_addr);

	}

	sendto(sockfd, buff, len, 0,
				(struct sockaddr*)&clientaddr, sizeof(clientaddr));
	return 0;
}
