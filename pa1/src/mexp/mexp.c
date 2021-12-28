#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int *funcIfExpIsZero(int *matrix, int row, int exp)
{
    int start = 0;
    for (int i = 0; i < row * row; i++)
    {
        if (i == start)
        {
            matrix[i] = 1;
            start += row + 1;
        }
        else
        {
            matrix[i] = 0;
        }
    }
    return matrix;
}

int *expFunc(int *answerMatrix, int *inputmatrix, int k, int exp, int recursive)
{

    //matrix to power of 1 is matrix itself
    if (exp == 1)
    {
        return answerMatrix;
    }
    //matrix mult is complete
    if (exp == recursive)
    {

        return answerMatrix;
    }

    int *rowArray;
    rowArray = calloc(k, sizeof(int *));

    int *colArray;
    colArray = calloc(k, sizeof(int *));

    int *dummyMatrix;
    dummyMatrix = calloc(k * k, sizeof(int *));
    int dummyCount = 0;

    for (int row = 0; row < k; row++)
    {
        //finds the values of row for first matrix
        for (int x = row * k, start = 0; start < k && x < x + k; x++, start++)
        {
            rowArray[start] = answerMatrix[x];
        }
    
        for (int col = 0; col < k; col++)
        {
            //finds values of col for seconf matrix
            for (int y = col, start = 0; start < k && y < k * k; y += k, start++)
            {
                colArray[start] = inputmatrix[y];
            }

            //doing matrix multiplication and plugging it into correct position
            int sum = 0;
            for (int i = 0; i < k; i++)
            {
                sum += rowArray[i] * colArray[i];
            }

            if (dummyCount != k * k)
            {
                dummyMatrix[dummyCount++] = sum;
            }
        }
    }

    //answerMatrix = intdup(dummyMatrix, k*k);

    for (int i = 0; i < k * k; i++)
    {
        answerMatrix[i] = dummyMatrix[i];
    }

    free(dummyMatrix);
    free(rowArray);
    free(colArray);
    recursive++;
    return expFunc(answerMatrix, inputmatrix, k, exp, recursive);
}

int main(int argc, char *argv[])
{
    if (!argv[1])
    {
        exit(EXIT_FAILURE);
    }

    int cap = strlen(argv[1]);
    int i = 0;
    char *file = malloc(cap + 1);
    
    while (i < cap)
    {
        *(file + i) = argv[1][i];
        i++;
    }
    char terminatingChar = '\0';
    *(file + cap) = terminatingChar;

    FILE *finalFile = fopen(file, "r");
    int row;
    fscanf(finalFile, "%d", &row);

    
    int num = 0;
    int *matrix;
    matrix = calloc(row * row, sizeof(int *));
    
    for (int i = 0; i < row * row; i++)
    {
        fscanf(finalFile, "%d", &num);
        matrix[i] = num;
    }

    int exp;
    fscanf(finalFile, "%d", &exp);


    int *answer;
    int *leftMatrix;
    leftMatrix = calloc(row * row, sizeof(int *));

   
    for (int i = 0; i < row * row; i++)
    {
        leftMatrix[i] = matrix[i];
    }

    if (exp == 0)
    {

        answer = funcIfExpIsZero(matrix, row, exp);
        int count = 0;
        int space = 0;
        for (int i = 1; i < row * row; i++)
        {
            printf("%d", answer[i]);
            if (space < row - 1)
            {
                printf(" ");
                space++;
            }
            count++;
            if (count == row)
            {
                printf("\n");
                count = 0;
                space = 0;
            }
        }
    }
    else
    {
        int recursive = 1;
        answer = expFunc(leftMatrix, matrix, row, exp, recursive);
        int count = 0;
        int space = 0;
        for (int i = 0; i < row * row; i++)
        {
            printf("%d", answer[i]);
            if (space < row - 1)
            {
                printf(" ");
                space++;
            }

            count++;
            if (count == row)
            {
                printf("\n");
                count = 0;
                space = 0;
            }
        }
    }

    free(leftMatrix);
    free(matrix);
    free(file);
    fclose(finalFile);
 
}