#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define ARR_LENGTH 10

int Product(int *arr, int *prod)
{
#pragma omp task shared(prod)
    {
        for (int i = 0; i < ARR_LENGTH; i++)
        {
#pragma omp atomic

            *prod *= arr[i];
        }
    }
}
int Sum(int *arr, int *sum)
{
#pragma omp task shared(sum)
    {
        for (int i = 0; i < ARR_LENGTH; i++)
        {
#pragma omp atomic

            *sum += arr[i];
        }
    }
}
int Max(int *arr)
{
    int max = arr[0];
    for (int i = 0; i < ARR_LENGTH; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}
int main()
{
    // Make array
    int arr[ARR_LENGTH];
    for (int i = 0; i < ARR_LENGTH; i++)
    {
        arr[i] = rand() % 10;
        printf("%d ", arr[i]);
    }
    printf("\n");

    int prod = 1, sum = 0, max;
// parallel
#pragma omp parallel sections
    {
#pragma omp section
        {
            Product(arr, &prod);
        }
#pragma omp section
        {
            Sum(arr, &sum);
        }
#pragma omp section
        {
            max = Max(arr);
        }
    }
    printf("Product: %d\n", prod);
    printf("Sum: %d\n", sum);
    printf("Max: %d\n", max);

    return 0;
}