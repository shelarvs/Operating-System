#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
 
#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (ph_num+4)%N
#define RIGHT (ph_num+1)%N
 
sem_t mutex;
sem_t seats[N];
 
void * philospher(void *num);
void take_fork(int);
void put_fork(int);
void test(int);
 
int state[N];
int phil_num[N]={0,1,2,3,4};
 
int main()
{
    int i;
    pthread_t thread_id[N];
    sem_init(&mutex,0,1);
    for(i=0;i<N;i++)
        sem_init(&seats[i],0,0);
    for(i=0;i<N;i++)
    {
        pthread_create(&thread_id[i],NULL,philospher,&phil_num[i]);
        printf("\nPhilosopher %d is thinking",i+1);
    }
    for(i=0;i<N;i++)
        pthread_join(thread_id[i],NULL);
}
 
void *philospher(void *num)
{
    while(1)
    {
        int *i = num;
        sleep(1);
        take_fork(*i);
        sleep(0);
        put_fork(*i);
    }
}
 
void take_fork(int ph_num)
{
    sem_wait(&mutex);
    state[ph_num] = HUNGRY;
    printf("\nPhilosopher %d is Hungry",ph_num+1);
    test(ph_num);
    sem_post(&mutex);
    sem_wait(&seats[ph_num]);
    sleep(1);
}
 
void test(int ph_num)
{
    if (state[ph_num] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        state[ph_num] = EATING;
        sleep(10);
        printf("\nPhilosopher %d takes fork %d and %d",ph_num+1,LEFT+1,ph_num+1);
        printf("\nPhilosopher %d is Eating",ph_num+1);
        sem_post(&seats[ph_num]);
    }
}
 
void put_fork(int ph_num)
{
    sem_wait(&mutex);
    state[ph_num] = THINKING;
    printf("\nPhilosopher %d putting fork %d and %d down",ph_num+1,LEFT+1,ph_num+1);
    printf("\nPhilosopher %d is thinking",ph_num+1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}
