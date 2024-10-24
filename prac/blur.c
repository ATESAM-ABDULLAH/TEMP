#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ROWS 10000
#define COLS 10000
#define KERNEL_SIZE 2

int matrix[ROWS][COLS], blurred_matrix[ROWS][COLS];

void blur_matrix(int Rows, int Cols)
{
    int kernel_sum = KERNEL_SIZE * KERNEL_SIZE; // Sum of kernel elements

#pragma omp parallel for collapse(2)
    for (int row = 0; row < Rows; ++row) // matrix row
    {
        for (int col = 0; col < Cols; ++col) // matrix col
        {
            int sum = 0;                                      // kernel sum on curr element
            for (int k_row = 0; k_row < KERNEL_SIZE; ++k_row) // kernel row
            {
                for (int k_col = 0; k_col < KERNEL_SIZE; ++k_col) // kernel col
                {
                    sum += matrix[row + k_row][col + k_col];
                }
            }
            blurred_matrix[row][col] = sum / kernel_sum;
        }
    }
}

int main()
{
    double start_time, end_time;
    double duration;

    // Initialize matrix with some values
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            matrix[i][j] = rand() % 100;
            // printf("%d ", matrix[i][j]);
        }
        // printf("\n");
    }

    start_time = omp_get_wtime();
    blur_matrix(ROWS, COLS);
    end_time = omp_get_wtime();
    duration = end_time - start_time;

    printf("Seconds: %f\n", duration);

    return 0;
}