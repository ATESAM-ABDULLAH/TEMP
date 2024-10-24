#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    int start;
    int end;
    int *arr1;
    int *arr2;
    int *arr3;
} thread_args;

void *sum(void *arg)
{
    thread_args *args = (thread_args *)arg;
    int *arr1 = args->arr1;
    int *arr2 = args->arr2;
    int *arr3 = args->arr3;

    int start = args->start;
    int end = args->end;

    for (int i = start; i < end + 1; i++)
    {
        arr3[i] = arr1[i] + arr2[i];
    }
    pthread_exit(NULL);
}

int main()
{
    int arr_size, num_t;

    printf("Enter array size: ");
    scanf("%d", &arr_size);

    int arr1[arr_size];
    int arr2[arr_size];
    int arr3[arr_size];

    printf("Enter array 1: \n");
    for (int i = 0; i < arr_size; i++)
    {
        scanf("%d", &arr1[i]);
    }

    printf("\nEnter array 2: \n");
    for (int i = 0; i < arr_size; i++)
    {
        scanf("%d", &arr2[i]);
    }

    printf("Enter number of Threads: ");
    scanf("%d", &num_t);

    thread_args args[num_t];
    for (int i = 0; i < num_t; i++)
    {
        int s = i * (arr_size / num_t);
        int e = s + (arr_size / num_t);

        if (i == (num_t - 1))
            e = arr_size - 1;

        args[i].start = s;
        args[i].end = e;
        args[i].arr1 = arr1;
        args[i].arr2 = arr2;
        args[i].arr3 = arr3;
    }

    pthread_t tid[num_t];
    for (int i = 0; i < num_t; i++)
    {
        pthread_create(&tid[i], NULL, sum, (void *)&args[i]);
    }

    for (int i = 0; i < num_t; i++)
        pthread_join(tid[i], NULL);

    printf("Result: ");
    for (int i = 0; i < arr_size; i++)
    {
        printf("%d ", arr3[i]);
    }
}