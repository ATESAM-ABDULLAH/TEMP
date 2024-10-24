/***
 Mat mul
    - input mat1,mat2 from file
    - res = mat1 x mat2
    - if mat1, mat2 not comaptible
        check transpose
    - elementwise sum res
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper func to close files
void close_files(FILE *f1, FILE *f2)
{
    fclose(f1);
    fclose(f2);
}

int main(int argc, char const *argv[])
{
    // input files missing
    if (argc < 3)
    {
        printf("Usage: [file1] [file2]\n");
        exit(-1);
    }

    // Open Files
    FILE *f1 = fopen(argv[1], "r");
    FILE *f2 = fopen(argv[2], "r");

    // Files not opened
    if (f1 == NULL || f2 == NULL)
    {
        printf("Input file not found.\n");
        exit(-2);
    }

    // read rows/cols for both files
    int row1, col1, row2, col2;
    fscanf(f1, "%d %d", &row1, &col1);
    fscanf(f2, "%d %d", &row2, &col2);

    // create 2d arrays
    int mat1[row1][col1];
    int mat2[row2][col2];
    int tra[col2][row2];

    // read mat1 from file
    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col1; j++)
        {
            if (fscanf(f1, "%d", &mat1[i][j]) != 1)
            {
                fprintf(stderr, "Error reading matrix data (%s).\n", argv[1]);
                close_files(f1, f2);
                exit(-5);
            }
        }
    }

    // read mat2 from file
    for (int i = 0; i < row2; i++)
    {
        for (int j = 0; j < col2; j++)
        {
            if (fscanf(f2, "%d", &mat2[i][j]) != 1)
            {
                fprintf(stderr, "Error reading matrix data (%s).\n", argv[2]);
                close_files(f1, f2);
                exit(-5);
            }
        }
    }

    int flag = 0; // flag if tranpose done

    // if dimensions are incompatible -> Transpose mat2
    if (col1 != row2)
    {
        printf(" Matrix dimensions incompatible. Trying Transpose\n");

        flag = 1;

        // transpose
        for (int i = 0; i < row2; i++)
        {
            for (int j = 0; j < col2; j++)
            {
                tra[j][i] = mat2[i][j]; // swap rows and cols
            }
        }

        // swap row, col vars
        int temp = row2;
        row2 = col2;
        col2 = temp;

        // print transpose -> debug
        for (int i = 0; i < row2; ++i)
        {
            for (int j = 0; j < col2; ++j)
            {
                printf(" %d", tra[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        // mat mul not possible
        if (col1 != row2)
        {
            printf("Matrix dimensions still incompatible.\n");
            close_files(f1, f2);
            exit(-1);
        }
    }

    int res[row1][col2];

    // cross multiply mat1 and mat2
    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col2; j++)
        {
            res[i][j] = 0; // initialize res to 0
            for (int k = 0; k < col1; k++)
            {
                if (flag) // transpose done
                    res[i][j] += mat1[i][k] * tra[k][j];
                else
                    res[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    printf("\nmat1 x mat 2 = \n");
    // print result -> debug
    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col2; j++)
        {
            printf(" %d", res[i][j]);
        }
        printf("\n");
    }

    int sum = 0;
    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col2; j++)
        {
            sum += res[i][j];
        }
    }

    printf("\nElementwise sum of A = %d\n", sum);

    return 0;
}
