#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	pid_t pid;
	
	pid=fork();
	
	if(pid==0)
	{
		sleep(20);
		printf("\nThis is child process\n");
		printf("\nMy process id is:%d\n",getpid());
		printf("\nMy parent process id is:%d\n",getppid());
		
	}
	
	else
	{
		sleep(2);
		printf("\nMy process id is:%d\n",getpid());
		printf("\nMy parent process id is:%d\n",getppid());
	}

	return(0);
}
