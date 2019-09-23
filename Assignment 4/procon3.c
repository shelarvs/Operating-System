#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdlib.h>
#define SIZE 5
#define TRUE 1

void *producer(void *);
void *consumer(void *);

int buffer[SIZE],count=0,in=0,out=0;
pthread_mutex_t m;
sem_t available;
sem_t occupied;

int main()
{
	int pno,cno,i=0;
	pthread_t ptid[SIZE],ctid[SIZE];
	pthread_mutex_init(&m,0);
	sem_init(&available,0,SIZE);
	sem_init(&occupied,0,0);
	
	printf("\nEnter the number of producers:");
	scanf("%d",&pno);
	
	printf("\nEnter the number of consumers:");
	scanf("%d",&cno);
	
	for(i=0;i<pno;i++)
	{
		pthread_create(&ptid[i],NULL,(void *)&producer,&i);
	}	
	
	for(i=0;i<cno;i++)
	{
		pthread_create(&ctid[i],NULL,(void *)&consumer,&i);
	}
	
	for(i=0;i<pno;i++)
	{
		pthread_join(ptid[i],NULL);
	}		
	
	for(i=0;i<cno;i++)
	{
		pthread_join(ctid[i],NULL);
	}
	
	pthread_mutex_destroy(&m);
	sem_destroy(&available);
	sem_destroy(&occupied);
	
	return(0);
	
}

void *producer(void *thread_no)
{
	int *n;
	n=(int *)thread_no;
	
	while(TRUE)
	{
		sem_wait(&available);
		
		pthread_mutex_lock(&m);
		
		if(count>=5)
		{
			printf("\nThe buffer is full!!!\n");
		}
		
		else
		{
			buffer[in]=rand()%100;
			printf("\nProducer %d produced %d\n",*n,buffer[in]);
			
			in=in+1;
			in=in%SIZE;
			count++;	
	
		}
		
		pthread_mutex_unlock(&m);
		
		sem_post(&occupied);
	
		sleep(1);
			
	}

	pthread_exit(0);
	
}

void *consumer(void *thread_no)
{
	int *n;
	n=(int *)thread_no;
	
	while(TRUE)
	{
		sem_wait(&occupied);
		
		pthread_mutex_lock(&m);
		
		if(count<=0)
		{
			printf("\nThe buffer is empty!!!\n");
		}
		
		else
		{
			printf("\nConsumer %d consumed %d\n",*n,buffer[out]);
			out=out+1;
			out=out%SIZE;
			count--;
			
		}
	
		pthread_mutex_unlock(&m);
	
		sem_post(&available);
	
		sleep(1);
	}

	pthread_exit(0);

}
