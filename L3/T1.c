#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_id(void *arg)
{
    int id = (int)(long)arg;
    printf("Hello from %d\n", id);
    pthread_exit(NULL);
}

int main()
{
    int n = 5;
    pthread_t tid[n];

    for (int i = 0; i < n; i++)
    {
        printf("Spawn %d\n", i);
        pthread_create(&tid[i], NULL, print_id, (void *)(long)i);
    }

    for (int i = 0; i < n; i++)
        pthread_join(tid[i], NULL);
}