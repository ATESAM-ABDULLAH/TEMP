#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_CARS 4
#define NUM_CHECKPOINTS 5

pthread_barrier_t barrier;

void *car_function(void *arg)
{
    int car_number = (int)arg;
    for (int i = 0; i < NUM_CHECKPOINTS; i++)
    {
        printf("Car %d reached checkpoint %d\n", car_number, i + 1);
        pthread_barrier_wait(&barrier);
    }

    printf("\n");
    printf("Car %d finished the race\n", car_number);
    return NULL;
}

int main()
{
    pthread_t cars[NUM_CARS];

    pthread_barrier_init(&barrier, NULL, NUM_CARS); // barrier waits for NUM_CARS

    for (int i = 0; i < NUM_CARS; i++)
    {
        pthread_create(&cars[i], NULL, car_function, (void *)i + 1);
    }

    for (int i = 0; i < NUM_CARS; i++)
    {
        pthread_join(cars[i], NULL);
    }

    pthread_barrier_destroy(&barrier);

    return 0;
}