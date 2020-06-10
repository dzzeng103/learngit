/*************************************************************************
    > File Name: pipetest.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Wed 22 Apr 2020 12:02:04 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>

int main(int argc, char **argv)
{
	int fd[2];
	char *cmd1[3] = {"cat", "/etc/hosts", NULL};
	char *cmd2[3] = {"grep", "dzzeng", NULL};
	int i = 0;

	if(pipe(fd) < 0)
	{
		fprintf(stderr, "pipe create error\n");
		exit(1);
	}

	pid_t pid;
	for(i = 0; i < 2; i++)
	{
		pid = fork();
		if(pid < 0)
		{
			printf("fork err\n");
			exit(1);
		}
		else if(pid > 0)
		{
			if(i == 2)
			{
				close(fd[0]);
				close(fd[1]);
				wait(0);
				wait(0);
			}
		}
		else
		{
			if(i == 0)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				execvp(cmd1[0], cmd1);
				break;
			}

			if(i == 1)
			{
				close(fd[1]);
				dup2(fd[0], STDIN_FILENO);
				close(fd[0]);
				execvp(cmd2[0], cmd2);
				break;
			}
		}
	}
}
