#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define MaxItems 1000 // Maximum items a producer can produce or a consumer can consume
#define BufferSize 10

pthread_mutex_t mutex;
sem_t full;
sem_t empty;

int in = 0;
int out = 0;
int buffer[BufferSize];
int allcount = 0;

void *producer(void *pno)
{
    int item;
    for (int i = 0; i < MaxItems; i++)
    {
        item = *((int *)pno);
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pno), buffer[in], in);
        in = (in + 1) % BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

void *consumer(void *cno)
{
    while (allcount < (10000 - 3))
    {
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n", *((int *)cno), item, out);
        out = (out + 1) % BufferSize;
        allcount++;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

int main()
{

    pthread_t pro[10], con[6];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&full, 0, BufferSize);
    sem_init(&empty, 0, 0);

    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // Just used for numbering the producer and consumer

    for (int i = 0; i < 10; i++)
    {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }
    for (int i = 0; i < 6; i++)
    {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }

    for (int i = 0; i < 10; i++)
    {
        pthread_join(pro[i], NULL);
    }
    for (int i = 0; i < 6; i++)
    {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);
    printf("Consumed = %d", allcount);
    return 0;
}