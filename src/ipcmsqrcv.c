/*************************************************************************
    > File Name: src/ipcmsqrcv.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Thu 23 Apr 2020 02:20:52 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/ipc.h>

typedef struct{
	long type;
	int start;
	int end;
}MSG;

int main(int argc, char **argv)
{
	if(argc < 3)
	{
		printf("error argc\n");
		exit(1);
	}
	
	key_t key = atoi(argv[1]); 
	long type = atoi(argv[2]);
	int msq_id;
	MSG msgr;
	
	if((msq_id = msgget(key, 0777)) < 0)
	{
		perror("msgget error");
	}
	if(msgrcv(msq_id, &msgr, sizeof(MSG) - sizeof(long), type, IPC_NOWAIT) < 0)
	{
		perror("msgrcv error");
	}
	else
	{
		printf("type:%d,start:%d, end:%d\n",
							msgr.type, msgr.start, msgr.end);
	}
}
