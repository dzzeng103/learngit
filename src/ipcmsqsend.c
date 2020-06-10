/*************************************************************************
    > File Name: src/ipcmsqsend.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Thu 23 Apr 2020 01:59:47 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<unistd.h>

typedef struct{
	long type;
	int start;
	int end;
}MSG;

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("the argc is absent");
		exit(1);
	}

	key_t key = atoi(argv[1]);
	printf("key:%d\n", key);
	int msq_id;
	if((msq_id = msgget(key, IPC_CREAT|IPC_EXCL|0777)) < 0)
	{
		perror("msgget error");
	}

	printf("msq_id:%d\n", msq_id);
	MSG msg1 = {1, 10, 100};
	MSG msg2 = {2, 20, 200};

	if(msgsnd(msq_id, &msg1, sizeof(MSG)-sizeof(long), IPC_NOWAIT) < 0)
	{
		perror("msgsnd faild");
	}
	if(msgsnd(msq_id, &msg2, sizeof(MSG)-sizeof(long), IPC_NOWAIT) < 0)
	{
		perror("msgsnd faild");
	}

	struct msqid_ds ds;
	if(msgctl(msq_id, IPC_STAT, &ds) < 0)
	{
		perror("msgctl faild");
	}
	printf("%d\n", ds.msg_qnum);
}
