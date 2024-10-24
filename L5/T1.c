#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_ITEMS 10

int buffer;
int full = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;

void *producer(void *arg)
{
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        pthread_mutex_lock(&mutex);

        while (full) // Wait if buffer is full
        {
            pthread_cond_wait(&not_full, &mutex);
        }

        buffer = rand() % 100; // Produce an item
        printf("Produced: %d\n", buffer);
        full = 1;

        pthread_cond_signal(&not_empty); // Signal that buffer has an item
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        pthread_mutex_lock(&mutex);

        while (!full) // Wait if buffer is empty
        {
            printf("Consumer: Waiting for the producer to produce...\n");
            pthread_cond_wait(&not_empty, &mutex);
        }

        int item = buffer; // Consume an item
        printf("Consumed: %d\n", item);
        full = 0;

        pthread_cond_signal(&not_full); // Signal that buffer has space
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t prod_thread, cons_thread;

    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    return 0;
}