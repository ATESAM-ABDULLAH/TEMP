#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10 // Adjust the array size as needed

int array[ARRAY_SIZE];
int even_count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *calculate_even_count(void *arg)
{
    int start = (int)arg;
    int end = start + ARRAY_SIZE / 4;
    int local_count = 0;

    for (int i = start; i < end; i++)
    {
        if (array[i] % 2 == 0)
        {
            local_count++;
        }
    }

    pthread_mutex_lock(&mutex);
    even_count += local_count;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    srand(time(NULL));

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = rand() % 100;
        printf("%d ", array[i]);
    }

    pthread_t threads[4];
    for (int i = 0; i < 4; i++)
    {
        pthread_create(&threads[i], NULL, calculate_even_count, (void *)(i * ARRAY_SIZE / 4));
    }

    // Wait for all threads to finish
    for (int i = 0; i < 4; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("\nNumber of even numbers: %d\n", even_count);

    return 0;
}