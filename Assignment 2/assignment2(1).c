#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int asc_bubble_sort(int [],int);
int desc_bubble_sort(int [],int);

int main()
{
	int a[10],n,i=0;
	pid_t pid;
	
	printf("Enter the size of the array:");
	scanf("%d",&n);
	
	printf("\nEnter the elements of the array:\n");
	
	for(i=0;i<n;i++)
	{
		printf("\nEnter the element at position a[%d]:",i);
		scanf("%d",&a[i]);
	}
	
	pid=fork();
	
	switch(pid)
	{
		case -1:
			printf("Fork error\n");
			
			exit(-1);
			
		case 0:
			printf("\nChild process\n");
			asc_bubble_sort(a,n);
			
			exit(0);
			
		default:
			sleep(5);
			printf("\n\nParent process");
			desc_bubble_sort(a,n);
			
			exit(0);
	
	}
	
	return(0);

}

int asc_bubble_sort(int a[10],int n)
{
	int i=0,j=0,temp;
	
	for(i=1;i<n;i++)
	{
		for(j=0;j<n-1;j++)
		{
			if(a[j]>a[i])
			{
				temp=a[j];
				a[j]=a[i];
				a[i]=temp;
			}
			
		}
		
	}

	printf("\nAfter sorting the elements of the array in ascending order:\n");
	printf("\n");
	
	for(i=0;i<n;i++)
	{
		printf("%d\t",a[i]);
	}
	
}

int desc_bubble_sort(int a[10],int n)
{
	int i=0,j=0,temp;
	
	for(i=1;i<n;i++)
	{
		for(j=0;j<n-1;j++)
		{
			if(a[j]<a[i])
			{
				temp=a[j];
				a[j]=a[i];
				a[i]=temp;
			}
			
		}
		
	}	
	
	printf("\n");
	printf("\nAfter sorting the elements of the array in descending order:\n");
	printf("\n");
	
	for(i=0;i<n;i++)
	{
		printf("%d\t",a[i]);
	}
	
}
