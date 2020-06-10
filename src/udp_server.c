/************************************************************************
    > File Name: udp_server.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Mon 20 Apr 2020 02:43:37 AM PDT
 ************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <memory.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>

int sockfd;

int sig_handle(int signo)
{
	if(signo == SIGINT)
	{
		printf("signo SIGINT\n");
		close(sockfd);
		exit(1);
	}
}
void show_addr(struct sockaddr_in addr)
{
	int port = ntohs(addr.sin_port);
	char ip[16];
	size_t len = sizeof(ip);

	inet_ntop(AF_INET, &addr.sin_addr.s_addr, ip, len);

	printf("port:%d, ip:%s\n", port, ip);
}

void do_server(char *buff)
{
	printf("----%s\n", buff);
}

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("argc err\n");
		exit(1);
	}

	signal(SIGINT, sig_handle);
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_port = htons(atoi(argv[1]));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = INADDR_ANY;

	if(bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
	{
		perror("bind err");
		exit(1);
	}
	
	struct sockaddr_in clientaddr;
	char buff[512];
	size_t lenth = sizeof(buff);
	
	while(1)
	{
		memset(&clientaddr, 0, sizeof(clientaddr));
		recvfrom(sockfd, buff, lenth, 0,
				(struct sockaddr*)&clientaddr, sizeof(&clientaddr));
		printf("port:%d\n", clientaddr.sin_port);
		show_addr(clientaddr);
		do_server(buff);
	}

	return 0;
}
