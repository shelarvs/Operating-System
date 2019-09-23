#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

typedef struct Matrix
{
	int *mat1;
	int *mat2;
	int r1,c1,r2,c2;
	
}Matrix;

void *multiplication(void *);

int main()
{
	int *a,*b,m1,n1,m2,n2,i,j;
	Matrix m;
	pthread_t tid;
	void *arg;
	
	printf("\nEnter the number of rows of first matrix:");
	scanf("%d",&m1);
	
	printf("\nEnter the number of columns of first matrix:");
	scanf("%d",&n1);
	
	a=(int *)malloc(m1*n1*sizeof(int));
	
	printf("\nEnter the elements of the first matrix:\n");

	for(i=0;i<m1;i++)
	{
		for(j=0;j<n1;j++)
		{
			scanf("%d",&*(a+i*n1+j));
		}
		
	}
	
	printf("\nEnter the number of rows of the second matrix:");
	scanf("%d",&m2);
	
	printf("\nEnter the number of columns of the second matrix:");
	scanf("%d",&n2);
	
	b=(int *)malloc(m2*n2*sizeof(int));
	
	printf("\nEnter the elements of the second matrix:\n");
	
	for(i=0;i<m2;i++)
	{
		for(j=0;j<n2;j++)
		{
			scanf("%d",&*(b+i*n2+j));
		}
		
	}
	
	m.mat1=a;
	m.mat2=b;
	m.r1=m1;
	m.c1=n1;
	m.r2=m2;
	m.c2=n2;
	
	arg=&m;
	pthread_create(&tid,NULL,(void *)&multiplication,arg);
	pthread_join(tid,NULL);
		
	return(0);

}

void *multiplication(void *arg)
{
	int *a,*b,*c,m1,n1,m2,n2,i,j,k;
	Matrix *n;
	n=(Matrix *)arg;
	
	m1=n->r1;
	n1=n->c1;
	
	m2=n->r2;
	n2=n->c2;
	
	a=(int *)malloc(m1*n1*sizeof(int));
	b=(int *)malloc(m2*n2*sizeof(int));
	c=(int *)malloc(m1*n2*sizeof(int));
	
	a=n->mat1;
	b=n->mat2;
	
	for(i=0;i<m1;i++)
	{
		for(j=0;j<n2;j++)
		{
			*(c+i*n2+j)=0;
			
			for(k=0;k<n1;k++)
			{
				*(c+i*n2+j)=*(c+i*n2+j)+(*(a+i*n1+k) * *(b+k*n2+j));
			}
			
		}
		
	}
	
	printf("\nMultiplication is:\n");
	
	for(i=0;i<m1;i++)
	{
		printf("\n");
		for(j=0;j<n2;j++)
		{
			printf("%d\t",*(c+i*n2+j));
		}
		
	}	
				
}
