#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define SIZE 5
#define TRUE 1
#define THINKING 0
#define HUNGRY 1
#define EATING 2

void *philosopher(void *);
int take_fork(int);
int test(int);
int LEFT(int);
int RIGHT(int);
int put_fork(int);

int phil_num[SIZE]={0,1,2,3,4},state[SIZE];
sem_t mutex;
sem_t S[SIZE];

int main()
{
	int i=0;
	pthread_t tid[SIZE];
	sem_init(&mutex,0,1);
	
	for(i=0;i<SIZE;i++)
	{
		sem_init(&S[i],0,0);
	}

	for(i=0;i<SIZE;i++)
	{
		pthread_create(&tid[i],NULL,(void *)&philosopher,&phil_num[i]);
		printf("\nPhilosopher %d is thinking\n",phil_num[i]);
	}
	
	for(i=0;i<SIZE;i++)
	{
		pthread_join(tid[i],NULL);
	}
	
	return(0);

}

void *philosopher(void *num)
{
	int *n;
	n=(int *)num;
	
	while(TRUE)
	{
		sleep(1);
		take_fork(*n);
		sleep(0);
		put_fork(*n);	
	}
	
}

int take_fork(int n)
{
	sem_wait(&mutex);
	state[n]=HUNGRY;
	printf("\nPhilosopher %d is hungry\n",n);
	test(n);	
	sem_post(&mutex);
	sem_wait(&S[n]);
	sleep(1);

}

int test(int n)
{
	if(state[n]==HUNGRY && state[LEFT(n)]!=EATING && state[RIGHT(n)]!=EATING)
	{
		state[n]=EATING;
		sleep(2);
		printf("\nPhilosopher %d takes fork %d and %d\n",n,LEFT(n),RIGHT(n));
		printf("\nPhilosopher %d is eating\n",n);
		sem_post(&S[n]);
	}
	
}

int LEFT(int n)
{
	n=n+SIZE;
	return(n%SIZE);
}

int RIGHT(int n)
{
	n=n+1;
	return(n%SIZE);
}

int put_fork(int n)
{
	sem_wait(&mutex);
	state[n]=THINKING;
	printf("\nPhilosopher %d is putting down forks %d and %d\n",n,LEFT(n),RIGHT(n));
	printf("\nPhilosopher %d is thinking\n",n);
	test(LEFT(n));
	test(RIGHT(n));
	sem_post(&mutex);
	
}
