#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4

int main()
{
    int a = 10;
    int b = 20;
    int c = 0;
    int i;

#pragma omp parallel num_threads(NUM_THREADS)
    {
// Public variable: visible to all threads -> one single public copy
#pragma omp atomic
        a++;

        // Private variable: each thread has its own copy
        int private_var = omp_get_thread_num();

// Lastprivate variable: the value of the last iteration from thread is sent into outer scope
#pragma omp for lastprivate(i)
        for (i = 0; i < 10; ++i)
        {
            c += i;
        }

// Firstprivate variable: the initial value is copied into each thread from the outer scope
#pragma omp for firstprivate(b)
        for (i = 0; i < 15; ++i)
        {
            b *= 2;
        }

// Reduction variable: combines the values from all threads
#pragma omp for reduction(+ : c)
        for (i = 0; i < 5; ++i)
        {
            c += i;
        }

        printf("Thread %d: a = %d, b = %d, c = %d, private_var = %d, i = %d\n",
               omp_get_thread_num(), a, b, c, private_var, i);
    }

    printf("After parallel region: a = %d, b = %d, c = %d\n", a, b, c);

    return 0;
}