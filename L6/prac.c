#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int thread_id;

#pragma omp parallel private(thread_id)
    {

        thread_id = omp_get_thread_num();

        for (int i = 0; i < omp_get_max_threads(); i++)
        {
            if (i == omp_get_thread_num())
            {
                printf("Running: %d\n", thread_id);
            }
        }
    }
    return 0;
}