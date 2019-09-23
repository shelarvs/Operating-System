#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	int fd;
	char * myfifo = "/tmp/myfifo";
	mkfifo(myfifo,0666);
	
	char arr1[20],arr2[20];
	
	while(1)
	{
		fd = open(myfifo,O_WRONLY);
		fgets(arr2,20,stdin);
		write(fd,arr2,strlen(arr2)+1);
		close(fd);
		
		fd = open(myfifo,O_RDONLY);
		read(fd,arr1,20);
		printf("USER 2 : %s",arr1);
		close(fd);
	}


	return 0;
}
