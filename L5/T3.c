#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ARRAY_SIZE 100

int main()
{
    int arr[ARRAY_SIZE];
    int sum = 0;

    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++) // create array
    {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }
    printf("\n");

#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        sum += arr[i];
    }
    printf("Sum of the array: %d\n", sum);
}