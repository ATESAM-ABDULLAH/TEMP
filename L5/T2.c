#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_CARS_A 5
#define NUM_CARS_B 5

int road_A_green = 1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_a = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_b = PTHREAD_COND_INITIALIZER;

void *traffic_light_controller(void *arg) // control signal color
{
    while (1)
    {
        pthread_mutex_lock(&mutex);

        road_A_green = !road_A_green; // flip signal color

        printf("\nTraffic Light: Green for Road %c, Red for Road %c\n", road_A_green ? 'A' : 'B', road_A_green ? 'B' : 'A');

        // Tell both roads about their color
        if (road_A_green)

            pthread_cond_signal(&cond_a);
        else
            pthread_cond_signal(&cond_b);

        pthread_mutex_unlock(&mutex);

        sleep(1); // Change light every 5 seconds
    }
}

void *road_a_cars(void *arg)
{
    for (int i = 0; i < NUM_CARS_A; i++)
    {
        pthread_mutex_lock(&mutex);

        while (!road_A_green) // if road A is red
        {
            printf("Road A: Red light. Waiting...\n");
            pthread_cond_wait(&cond_a, &mutex);
        }

        printf("Road A: Green light! Cars passing...\n");

        pthread_mutex_unlock(&mutex);
    }
}

void *road_b_cars(void *arg)
{
    for (int i = 0; i < NUM_CARS_B; i++)
    {
        pthread_mutex_lock(&mutex);

        while (road_A_green) // if road A green -> road B is red
        {
            printf("Road B: Red light. Waiting...\n");
            pthread_cond_wait(&cond_b, &mutex);
        }

        printf("Road B: Green light! Cars passing...\n");

        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t traffic_light, road_a, road_b;

    pthread_create(&traffic_light, NULL, traffic_light_controller, NULL); // a thread takes care of te signal

    pthread_create(&road_a, NULL, road_a_cars, NULL);
    pthread_create(&road_b, NULL, road_b_cars, NULL);

    pthread_join(traffic_light, NULL);
    pthread_join(road_a, NULL);
    pthread_join(road_b, NULL);

    return 0;
}