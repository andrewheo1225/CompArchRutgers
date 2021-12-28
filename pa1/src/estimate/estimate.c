#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define arrsize 10

int columns;
int newcolumns;
int rows;
int newrows;

double **initialize(int size, int size2)
{

    double **initial = malloc(sizeof(double *) * size);
    for (int i = 0; i < size; i++)
    {
        initial[i] = malloc(sizeof(double) * size2);
    }

    return initial;
}

void printmatrix(double **matrix, int size)
{

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            printf("%.f\n", matrix[i][j]);
        }
    }
}

double **singleinitialize(int size)
{
    double **initial = malloc(sizeof(double *) * size);
    for (int i = 0; i < size; i++)
    {
        initial[i] = malloc(sizeof(double) * size);
    }

    return initial;
}

double **makeTranspose(double **m1)
{

    int newcol = columns;
    int newrow = rows;

    double **flipped = initialize(newcol, newrow);
    for (int i = 0; i < newrow; i++)
    {
        for (int j = 0; j < newcol; j++)
        {
            flipped[j][i] = m1[i][j];
        }
    }
    return flipped;
}

double **multiply(double **m1, double **m2, int check1, int check2, int checker1, int checker2)
{

    int row1 = check1;
    int row2 = check2;
    int col2 = checker2;

    double **final = initialize(row1, col2);
    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col2; j++)
        {
            final[i][j] = 0;
            for (int k = 0; k < row2; k++)
            {
                final[i][j] += (m1[i][k] * m2[k][j]);
            }
        }
    }

    return final;
}

void free_matrix(double **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

double **invert(double **m1)
{

    int check2 = columns;
    double **zero = singleinitialize(check2);
    for (int i = 0; i < check2; i++)
    {
        for (int j = 0; j < check2; j++)
        {
            if (i == j)
            {
                zero[i][j] = 1;
            }
            else
            {
                zero[i][j] = 0;
            }
        }
    }
    double diff;
    for (int i = 0; i < check2; i++)
    {
        diff = m1[i][i];
        for (int j = 0; j < check2; j++)
        {
            m1[i][j] /= diff;
            zero[i][j] /= diff;
        }
        for (int k = i + 1; k < check2; k++)
        {
            diff = m1[k][i];
            for (int z = 0; z < check2; z++)
            {
                m1[k][z] -= m1[i][z] * diff;
                zero[k][z] -= zero[i][z] * diff;
            }
        }
    }

    for (int a = check2 - 1; a >= 0; a--)
    {
        for (int i = a - 1; i >= 0; i--)
        {
            diff = m1[i][a];
            for (int j = 0; j < check2; j++)
            {
                m1[i][j] -= m1[a][j] * diff;
                zero[i][j] -= zero[a][j] * diff;
            }
        }
    }

    return zero;
}

int main(int argc, char *argv[])
{

    char rowlit[arrsize];

    FILE *file = fopen(argv[1], "r");
    fscanf(file, "%s", rowlit);

    fscanf(file, "%d %d", &columns, &rows);
    columns++;
    double **initial = initialize(rows, columns);

    double **initial2 = malloc(sizeof(double *) * rows);
    for (int i = 0; i < rows; i++)
    {
        initial2[i] = malloc(sizeof(double));
    }

    int count = 0;
    for (int i = 0; i < rows; i++)
    {
        int j = 0;
        while (j <= columns)
        {
            if (j == columns)
            {
                fscanf(file, "%lf", &initial2[count++][0]);
            }
            else if (j == 0)
            {
                initial[i][j] = 1;
            }
            else
            {
                fscanf(file, "%lf", &initial[i][j]);
            }
            j++;
        }
    }
    fclose(file);

    FILE *newfile = fopen(argv[2], "r");
    fscanf(newfile, "%s", rowlit);
    fscanf(newfile, "%d %d", &newcolumns, &newrows);
    newcolumns++;

    double **newmat = initialize(newrows, newcolumns);

    for (int i = 0; i < newrows; i++)
    {
        int j = 0;
        while (j < newcolumns)
        {
            if (j == 0)
            {
                newmat[i][j] = 1;
            }
            else
            {
                fscanf(newfile, "%lf", &newmat[i][j]);
            }
            j++;
        }
    }
    fclose(newfile);

    int row1;
    int row2;
    int col1;
    int col2;

    double **trap = makeTranspose(initial);
    printf("trap: \n");
    printmatrix(trap, row1);
    row1 = columns;
    row2 = rows;
    col1 = rows;
    col2 = columns;

    double **first = multiply(trap, initial, row1, row2, col1, col2);
    printf("multiply: \n");
    printmatrix(first, row1);

    double **inverse = invert(first);
    printf("invert: \n");
    printmatrix(inverse, row1);
    row1 = columns;
    col1 = columns;
    row2 = columns;
    col2 = rows;
    double **second = multiply(inverse, trap, row1, row2, col1, col2);
    printf("second: \n");
    printmatrix(second, row1);
    row1 = columns;
    col1 = rows;
    row2 = rows;
    col2 = 1;
    double **gaussed = multiply(second, initial2, row1, row2, col1, col2);
    printf("gaussed: \n");
    printmatrix(gaussed, row1);

    row1 = newrows;
    col1 = newcolumns;
    row2 = newcolumns;
    col2 = 1;

    double **final = multiply(newmat, gaussed, row1, row2, col1, col2);

    printmatrix(final, row1);

    free_matrix(initial, rows);
    free_matrix(initial2, rows);
    free_matrix(trap, columns);
    free_matrix(first, columns);
    free_matrix(inverse, columns);
    free_matrix(second, columns);
    free_matrix(gaussed, columns);
    free_matrix(newmat, newrows);
    free_matrix(final, newrows);

    exit(EXIT_SUCCESS);
}
