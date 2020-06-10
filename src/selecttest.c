#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>

//#define FD_SETSIZE 1024

int main(int argc, char **argv)
{
	if(argc < 2){printf("error\n");}
	
	//创建socket
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	
	//bind socket
	struct sockaddr_in saddr;
	
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(atoi(argv[1]));
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(listenfd, (struct sockaddr *)&saddr, sizeof(saddr));
	
	//listen
	listen(listenfd, 10);

	fd_set rset, allsets;
	int i, nready, client[FD_SETSIZE], connfd;
	int maxfd = listenfd;
	int maxi = -1;
	char buff[1024];
	int sockfd;

	for(i = 0; i < FD_SETSIZE; i++)
	{
		client[i] = -1;
	}
	bzero(&allsets, sizeof(allsets));
	FD_SET(listenfd, &allsets);

	while(1)
	{

		rset = allsets;
		nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
		printf("nready:%d, maxfd:%d, maxi:%d\n", nready, maxfd, maxi);

		if(nready < 0)
		{
			perror("select err");
			exit(1);	
		}
		if(FD_ISSET(listenfd, &rset))
		{
			printf("listen fd\n");
			if(connfd = accept(listenfd, NULL, NULL) < 0)
			{
				printf("accept err\n");
				break;
			}
			for(i=0; i<FD_SETSIZE; i++)
			{
				if(client[i] < 0)
				{
					client[i] = connfd;
					break;
				}
			}
			printf("i------:%d\n", i);

			if(i == FD_SETSIZE)
			{
				printf("fd_setsize yichu\n");
				exit(1);
			}
			FD_SET(connfd, &allsets);
			if(connfd > maxfd)
			{
				maxfd = connfd;
			}
			if(i > maxi)
			{
				maxi = i;
			}	
			
			if(--nready == 0)
			{
				continue;
			}
		}
		for(i = 0; i < maxi; i++)
		{
			if((sockfd = client[i]) < 0)
			{
				continue;
			}
			memset(buff, 0, sizeof(buff));
			if(read(sockfd, buff, sizeof(buff)) > 0)
			{
				printf("----------buff:%s\n", buff);
			}
			else
			{
				close(sockfd);
				printf("close fd\n");
				client[i] = -1;
				FD_CLR(sockfd, &allsets);
			}
			if(--nready == 0)
			{
				break;
			}
		}
		
	}
	close(listenfd);
	return 0;

}
