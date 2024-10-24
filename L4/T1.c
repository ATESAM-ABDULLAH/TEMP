#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define NUM_TRANSACTIONS 5
#define INITIAL_BALANCE 1000

int balance = INITIAL_BALANCE;
pthread_mutex_t mutex;

void *thread_function(void *arg)
{

    for (int i = 0; i < NUM_TRANSACTIONS; i++)
    {
        // pthread_mutex_lock(&mutex);

        int amount = rand() % 100 + 1; // rand amount

        if (rand() % 2 == 0) // rand choice
        {
            pthread_mutex_lock(&mutex);
            balance += amount;
            printf("Thread %d is depositing %d\n:  Balance = %d \n", (int)arg, amount, balance);
            pthread_mutex_unlock(&mutex);
        }
        else
        {
            if (amount <= balance)
            {
                pthread_mutex_lock(&mutex);
                balance -= amount;
                printf("Thread %d is withdrawing %d\n:  Balance = %d \n", (int)arg, amount, balance);
                pthread_mutex_unlock(&mutex);
            }
            else
            {
                printf("Thread %d: Insufficient funds\n", (int)arg);
            }
        }

        // pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, thread_function, (void *)i);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Final balance: %d\n", balance);

    pthread_mutex_destroy(&mutex);

    return 0;
}