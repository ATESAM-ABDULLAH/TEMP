#include <stdio.h>
#include <omp.h>

void parallel_loop(int n) {
    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        // Code to be executed in parallel
        printf("Thread %d: i = %d\n", omp_get_thread_num(), i);
    }
}

void parallel_section(int n) {
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            // Code for section 1
            printf("Section 1: Thread %d\n", omp_get_thread_num());
        }
        #pragma omp section
        {
            // Code for section 2
            printf("Section 2: Thread %d\n", omp_get_thread_num());
        }
    }
}

void parallel_task(int n) {
    #pragma omp parallel
    {
        #pragma omp single
        {
            // Code to be executed by a single thread
            printf("Single thread: Thread %d\n", omp_get_thread_num());
        }
        #pragma omp task
        {
            // Code for task 1
            printf("Task 1: Thread %d\n", omp_get_thread_num());
        }
        #pragma omp task
        {
            // Code for task 2
            printf("Task 2: Thread %d\n", omp_get_thread_num());
        }
    }
}

void parallel_reduction(int n) {
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; ++i) {
        sum += i;
    }
    printf("Sum: %d\n", sum);
}

int main() {
    int n = 10;

    parallel_loop(n);
    parallel_section(n);
    parallel_task(n);
    parallel_reduction(n);

    return 0;
}