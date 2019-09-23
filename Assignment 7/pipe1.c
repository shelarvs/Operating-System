#include<stdio.h>
#include<unistd.h>
//#include<sys/types.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	int fd1[2]={0,1},length1,fd2[2]={0,1},length2;
	char str1[30]={"Hello World!!!"};
	char str2[30]={"I am Nikhil Takawale"};
	pid_t pid;
	
	pipe(fd1);
	pipe(fd2);
	pid=fork();
	
	switch(pid)
	{
		case 0:
			sleep(1);
			printf("\nThis is child process\n");
			printf("\nThis child process is reading from pipe 1\n");
			length1=strlen(str1);
			read(fd1[0],str1,length1);
			printf("\nThe message read is:%s\n",str1);
			
			printf("\nThis child process is writing to pipe 2\n");
			length2=strlen(str2);
			write(fd2[1],str2,length2);
			printf("\nThe message written is:%s\n",str2);
			
			exit(0);
			
		case -1:
			printf("\nFork error\n");
			
			exit(-1);
			
		default:
			printf("\nThis is parent process\n");
			printf("\nThis parent process is writing to pipe 1\n");
			length1=strlen(str1);
			write(fd1[1],str1,length1);
			printf("\nThe message written is:%s\n",str1);
			
			printf("\nThis parent process is reading from pipe 2\n");
			length2=strlen(str2);
			read(fd2[0],str2,length2);
			printf("\nThe message read is:%s\n",str2);
	}

	return(0);

}
