#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	int fd1[2]={0,1},fd2[2]={0,1};
	char str1[20]={"HELLO IN ENGLISH"},str2[20]={"HOLA IN SPANISH"};
	pid_t pid;
	
	pipe(fd1);
	pipe(fd2);
	pid=fork();
	
	switch(pid)
	{
		case 0:
			printf("THIS IS CHILD PROCESS\n");
			printf("THE CHILD PROCESS IS READING FROM PIPE 1\n");
			read(fd1[0],str1,strlen(str1));
			printf("THE MESSAGE READ IS : %s\n",str1);
			
			printf("THE CHILD PROCESS IS WRITING IN PIPE 2\n");
			write(fd2[1],str2,strlen(str2));
			printf("THE MESSAGE WRITTEN BY CHILD PROCESS IS : %s\n",str2);
			exit(0);
			
		case -1:
			printf("FORK ERROR\n");
			exit(-1);
		
		default:
			printf("THIS IS PARENT PROCESS\n");
			printf("THE PARENT PROCESS IS WRITING IN PIPE 1\n");
			write(fd1[1],str1,strlen(str1));
			printf("THE MESSAGE WRITTEN BY PARENT PROCESS IS : %s\n",str1);
			
			printf("THE PARENT PROCESS IS READING FROM PIPE 2\n");
			read(fd2[0],str2,strlen(str2));
			printf("THE MESSAGE READ IS : %s\n",str2);
	}

	return 0;
}
