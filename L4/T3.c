#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MATRIX_SIZE 2

int A[MATRIX_SIZE][MATRIX_SIZE];
int B[MATRIX_SIZE][MATRIX_SIZE];
int C[MATRIX_SIZE][MATRIX_SIZE];

pthread_mutex_t mutex;
pthread_barrier_t barrier;

void *thread_function(void *arg)
{
    int row = (int)arg; // row num

    for (int j = 0; j < MATRIX_SIZE; j++) // loop over columns in row
    {
        C[row][j] = 0;
        for (int k = 0; k < MATRIX_SIZE; k++)
        {
            pthread_mutex_lock(&mutex);
            C[row][j] += A[row][k] * B[k][j];
            pthread_mutex_unlock(&mutex);
        }
        pthread_barrier_wait(&barrier);
    }
    return NULL;
}

int main()
{
    pthread_t threads[MATRIX_SIZE];

    // Create A, B with rand values
    srand(time(NULL));
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    // Print matrices
    printf("Matrix A:\n");
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    printf("Matrix B:\n");
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }
    //------------------------------------------------------------------------
    // Init
    pthread_mutex_init(&mutex, NULL);
    pthread_barrier_init(&barrier, NULL, MATRIX_SIZE);

    // Create threads for each row
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        pthread_create(&threads[i], NULL, thread_function, (void *)i);
    }

    // Join threads
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Print result
    printf("Matrix C:\n");
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    pthread_mutex_destroy(&mutex);
    pthread_barrier_destroy(&barrier);

    return 0;
}