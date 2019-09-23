#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int fd1;
	char * myfifo = "/tmp/myfifo";
	mkfifo(myfifo,0666);
	
	char str1[50],str2[50];
	
	while(1)
	{
		fd1 = open(myfifo,O_RDONLY);
		read(fd1,str1,50);
		printf("USER 1 : %s\n",str1);
		close(fd1);
		
		fd1 = open(myfifo,O_WRONLY);
		fgets(str2,50,stdin);
		write(fd1,str2,strlen(str2)+1);
		close(fd1);
	}
	
	return 0;	
}
