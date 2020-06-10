/*************************************************************************
    > File Name: src/http_server.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Fri 08 May 2020 06:59:57 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<memory.h>
#include<signal.h>
#include<pthread.h>
#include<errno.h>
#include<fcntl.h>

void *pth_data_get(void *lfd)
{
	char buff[1024];
	int ret = -1;
	int fd = *(int *)lfd;
	int flags;

#if 0
	flags = fcntl(fd, F_GETFL, 0);
	if(flags < 0)
	{
		printf("get flags err\n");
		exit(1);
	}
	flags |= O_NONBLOCK;
	fcntl(fd, F_SETFL, flags);
#endif
	pthread_detach(pthread_self());
	memset(&buff, 0, sizeof(buff));
	printf("---------FD:%d\n",fd);
	//char t;
	//ret = read(fd, &t, 1);
	//printf("000000000ret:%d, t:%c\n", ret, t);
	while(1)
	{
		ret = read(fd, buff, sizeof(buff));
		if(ret == 0)
		{
			printf("client unconnect...\n");
			pthread_exit("pthread exit");
		} 
		printf("---ret:%d,%d\n%s\n", ret, fd, buff);
	}

	printf("ret:%d\n", ret);
	close(fd);
	return;
}

void sig_handler(int signo)
{
	if(SIGINT == signo)
	{
		printf("CTRL + C intrrupt\n");
		exit(1);
	}
}
int main()
{
	if(signal(SIGINT, sig_handler) < 0)
	{
		printf("sig err\n");
		exit(1);
	}

	int sockfd;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		printf("sock err\n");
		exit(1);
	}

	struct sockaddr_in saddr;
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8989);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	
	bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr));
	listen(sockfd, 4);

	int lfd;
	pthread_t pid;
	int i = 0;
	while(1)
	{
		lfd = accept(sockfd, NULL, NULL);
		printf("lfd:%d\n",lfd);
		if(lfd > 0)
		{
			printf("lfd:%d\n", lfd);
			if(pthread_create(&pid, NULL, pth_data_get, (void *)&lfd) != 0)
			{
				printf("pthread create error:%d\n", errno);
				exit(1);
			}
			
		}
		
	}

	close(sockfd);
}
