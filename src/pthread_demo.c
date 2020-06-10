#include <stdio.h>
#include <pthread.h>

void *pthread_handle1(void *pth)
{
	
	while(1)
	{
		printf("this is a pthread1!\n");
		sleep(2);	
	}
}

void *pthread_handle2(void *pth)
{
	sleep(3);
	printf("this is a pthread2!\n");	
}

int main()
{
	pthread_t pid[2];
	char *buf;	
	
	pthread_create(&pid[0], NULL, pthread_handle1, NULL);
	pthread_create(&pid[1], NULL, pthread_handle2, NULL);
	pthread_join(pid[0], NULL);
	pthread_join(pid[1], NULL);

}
