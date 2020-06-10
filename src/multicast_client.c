/*************************************************************************
    > File Name: multicast_client.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Thu 07 May 2020 06:29:19 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<signal.h>
#include<memory.h>
#include<string.h>
#include<fcntl.h>

void sig_handle(int signo)
{
	if(signo == SIGINT)
	{
		printf("CTRL+C interdump\n");
		exit(1);
	}

}

int main(int argc, char **argv)
{
	if(argc < 2)
	{
			printf("argc err\n");
		exit(1);
	}
	if(signal(SIGINT, sig_handle) < 0)
	{
		printf("sig error\n");
		exit(1);
	}

	//creat sock
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	
	struct sockaddr_in caddr;
	memset(&caddr, 0, sizeof(caddr));

	caddr.sin_family = AF_INET;
	caddr.sin_port = htons(8888);
	caddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	inet_pton(AF_INET, "0.0.0.0", &caddr.sin_addr.s_addr);
	bind(sockfd, (struct sockaddr *)&caddr, sizeof(caddr));
	
	//setsockopt join multicast
	struct ip_mreqn fl;
	inet_pton(AF_INET, argv[1], &fl.imr_multiaddr.s_addr);
	inet_pton(AF_INET, "0.0.0.0", &fl.imr_address.s_addr);
	fl.imr_ifindex = if_nametoindex("ETH0");
	setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &fl, sizeof(fl));

	while(1)
	{
		char buff[1024] = {0};
		if(recvfrom(sockfd, buff, sizeof(buff), 0, NULL, NULL) < 0)
		{
			printf("recvfrom err\n");
			break;
		}
		printf("%s\n", buff);
	}
	close(sockfd);
}
