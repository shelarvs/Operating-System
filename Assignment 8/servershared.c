#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	int fd;
	
	char * myfifo = "/tmp/myfifo";
	mkfifo(myfifo,0666);
	
	char arr1[50],arr2[50];
	
	while(1)
	{
		fd = open(myfifo,O_WRONLY);
		fgets(arr2,50,stdin);
		write(fd,arr2,strlen(arr2)+1);
		close(fd);
		
		fd = open(myfifo,O_RDONLY);
		read(fd,arr1,50);
		printf("USER 2 : %s\t",arr1);
		close(fd);
	}
	
	
	return 0;
}
