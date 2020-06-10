/*************************************************************************
    > File Name: select_server.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Tue 28 Apr 2020 06:16:20 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<memory.h>
#include<netinet/in.h>
#include<sys/select.h>

int sockfd;
int main(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("argc error\n");
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in serveraddr;
	memset(serveraddr, 0, sizeof(serveraddr));

	serveraddr.sin_port = htons(atoi(argv[1]));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = INADDR_ANY;

	bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	listen(sockfd, 10);

	fd_set rdfds;
	int maxid, ret, clientfd;
	
	while(1)
	{
		FD_ZERO(&rdfds);
		FD_SET(socket, &rdfds);
		maxid = socket;
		ret = select(maxid + 1, &rdfds, NULL, NULL, NULL);
		for(clientfd)
		{

		}
		if(FD_ISSET())
		{

		}
	}


}
