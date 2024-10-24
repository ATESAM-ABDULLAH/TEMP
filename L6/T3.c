#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Function to compute the nth Fibonacci number
int fibonacci(int n)
{
    if (n <= 1)
        return n;

    int x, y;

#pragma omp task shared(x)
    x = fibonacci(n - 1);

#pragma omp task shared(y)
    y = fibonacci(n - 2);

#pragma omp taskwait
    return x + y;
}

int main()
{
    int n;

    // Prompt user for input
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    printf("Fibonacci series up to %d:\n", n);

#pragma omp parallel
    {
#pragma omp single
        {
            for (int i = 1;; i++)
            {
                int fib = fibonacci(i);
                if (fib < n) // prints fib(i)<n
                {
#pragma omp task
                    {

                        printf("%d, ", fib);
                    }
                }
                else
                {
                    printf("\n");
                    break;
                }
            }
        }
    }
    return 0;
}
