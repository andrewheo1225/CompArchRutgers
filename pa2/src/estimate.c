
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//   W == (X^T * X) ^-1 * X^T * Y ->
//   W*X' = Y'
void free_matrix(double** matrix, int size){
    for(int i = 0; i<size; i++){
        free(matrix[i]);
    }
    free(matrix);
}
double *transpose(double *matrix, int rows, int cols)
{
    int dummyI = 0;
    double *tranposeMatrix = calloc(rows * cols, sizeof(double *));
    int count = 0;
    while (dummyI < rows)
    {
        count++;
        double num;
        int dummyJ = 0;
        while (dummyJ < cols)
        {
            num = *(matrix + dummyI * cols + dummyJ);
            *(tranposeMatrix + dummyI + rows * dummyJ) = num;
            dummyJ++;
        }
        dummyI++;
    }
    return tranposeMatrix;
}

double **initializeDoublePointerArray(int size)
{
    double **initial = calloc(size, sizeof(double *));
    for (int i = 0; i < size; i++)
    {
        initial[i] = calloc(size, sizeof(double));
    }

    return initial;
}

double **inverse(double *doNotTouchMatrix, int rows, int cols)
{
    //finish delcaration
    double **answer = initializeDoublePointerArray(rows);

    int doNotTouchMatrixCount = 0;
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            answer[row][col] = doNotTouchMatrix[doNotTouchMatrixCount];
            doNotTouchMatrixCount++;
        }
    }

    double **identityMatrix = initializeDoublePointerArray(rows);
    double value;
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < rows; col++)
        {
            if (row == col)
            {
                identityMatrix[row][col] = 1;
            }
            else
            {
                identityMatrix[row][col] = 0;
            }
        }
    }

    
    for (int initial = 0; initial < rows; initial++)
    {
        value = answer[initial][initial];

        for (int second = 0; second < rows; second++)
        {
            answer[initial][second] /= value;
            identityMatrix[initial][second] /= value;
        }
        for (int last = initial + 1; last < rows; last++)
        {
            value = answer[last][initial];

            for (int z = 0; z < rows; z++)
            {
                answer[last][z] -= answer[initial][z] * value;
                identityMatrix[last][z] -= identityMatrix[initial][z] * value;
            }
        }
    }

    for (int first = rows - 1; first >= 0; first--)
    {
        for (int second = first - 1; second >= 0; second--)
        {
            value = answer[second][first];

            for (int j = 0; j < rows; j++)
            {
                answer[second][j] -= answer[first][j] * value;
                identityMatrix[second][j] -= identityMatrix[first][j] * value;
            }
        }
    }
    free_matrix(answer,rows);
    return identityMatrix;
}

double *multiply(double *leftMatrix, int leftmatrixROW, int leftmatrixCOL,
                 double *rightMatrix, int rightmatrixROW, int rightMatrixCOL)
{

    int stretch = 0;
    double *answer = calloc(leftmatrixROW * rightMatrixCOL, sizeof(double *));
    for (int x = 0; x < leftmatrixROW; x++)
    {
        stretch++;
        double lengthofArray = 0;
        for (int y = 0; y < rightMatrixCOL; y++)
        {
            double sum = 0.0;
            for (int k = 0; k < rightmatrixROW; k++)
            {
                lengthofArray++;
                sum = sum + leftMatrix[x * leftmatrixCOL + k] * rightMatrix[k * rightMatrixCOL + y];
            }

            answer[x * rightMatrixCOL + y] = sum;
        }
    }
    return answer;
}

void print(double *matrix, int row, int col)
{
    int nextLine = 0;
    for (int i = 0; i < row * col; i++)
    {
        printf("%f ", matrix[i]);
        nextLine++;
        if (nextLine == (col))
        {
            printf("\n");
            nextLine = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    //                                     TRAINING TXT
    if (!argv[1])
    {
        exit(EXIT_FAILURE);
    }

    int capTrain = strlen(argv[1]);
    int iTRAIN = 0;
    char *fileTrain = malloc(capTrain + 1);

    while (iTRAIN < capTrain)
    {
        *(fileTrain + iTRAIN) = argv[1][iTRAIN];
        iTRAIN++;
    }
    char terminatingCharTrain = '\0';
    *(fileTrain + capTrain) = terminatingCharTrain;
    FILE *training;
    training = fopen(fileTrain, "r");
    char name[10];
    int preTrainCol; //k = k+1
    int preTrainrow; //n = rows

    fscanf(training, "%s", name);
    fscanf(training, "%d", &preTrainCol);
    fscanf(training, "%d", &preTrainrow);
    //int trainCol = preTrainCol;
    preTrainCol++;

    double *preMatrix = calloc((preTrainCol)*preTrainrow, sizeof(double *));
    int sum = (preTrainCol)*preTrainrow;
    double num = 0;
    for (int i = 0; i < sum; i++)
    {
        fscanf(training, "%lf", &num);
        preMatrix[i] = num;
    }

    double *yTrainMatrix = calloc(preTrainrow, sizeof(double *));
    int starty = preTrainCol - 1;
    int index = 0;
    for (int i = 0; i < preTrainCol * preTrainrow; i++)
    {
        if (starty == i && index < preTrainrow)
        {
            yTrainMatrix[index++] = preMatrix[i];
            starty += preTrainCol;
        }
    }

    // printf("PreMatrix MATRIX: row: |%d| col: |%d| \n", preTrainrow, preTrainCol);
    // print(preMatrix, preTrainrow, preTrainCol);
    // printf("\n");

    // printf("Y MATRIX: row: \n");
    // print(yTrainMatrix, preTrainrow, 1);
    // printf("\n");


    //initialize left most column as 1
    double *matrix = calloc(preTrainCol * preTrainrow, sizeof(double*));
    int valToOne = 0;
    for(int i = 0; i < preTrainCol * preTrainrow; i++){
        if(valToOne == i) {
            matrix[i] = 1;
            valToOne+=preTrainCol;

        }
    }
    int leftmost = 0;
    for(int i = 0; i < preTrainCol * preTrainrow; i++){
        if(leftmost != i){
            matrix[i] = preMatrix[i-1];
        }else{
            leftmost+=preTrainCol;
        }
    }

    // printf("matrix after change: row: |%d| col: |%d| \n", preTrainrow, preTrainCol);
    // print(matrix, preTrainrow, preTrainCol);
    // printf("\n");
   

    //                                  INPUT TXT
    int cap = strlen(argv[2]);
    int i = 0;
    char *file = malloc(capTrain + 1);

    while (i < cap)
    {
        *(file + i) = argv[2][i];
        i++;
    }
    char terminatingChar = '\0';
    *(file + cap) = terminatingChar;
    FILE *input;
    input = fopen(file, "r");
    char nameInput[10];
    int inputCol; //# of attrinbutes
    int inputRow; //# of houses

    fscanf(input, "%s", nameInput);
    fscanf(input, "%d", &inputCol);
    fscanf(input, "%d", &inputRow);
   
    double *inputMatrix = calloc((inputCol)*inputRow, sizeof(double *));
    int sum2 = (inputCol)*inputRow;
    double num2 = 0;
    for (int i = 0; i < sum2; i++)
    {
        fscanf(input, "%lf", &num2);
        inputMatrix[i] = num2;
    }   
    inputCol++;

    double *changeInput = calloc(inputCol * inputRow, sizeof(double*));
    valToOne = 0;
    for(int i = 0; i < inputRow * inputCol; i++){
        if(valToOne == i) {
            changeInput[i] = 1;
            valToOne+=inputCol;

        }
    }

   
    int index2 = 0;
    for(int i = 0; i < inputCol * inputRow; i++){
        if(changeInput[i] != 1){
            changeInput[i] = inputMatrix[index2++];
        }
    }



    //                                  WORK
    
    double *transposeMatrix = transpose(matrix, preTrainrow, preTrainCol);
    int tranposeROW = preTrainCol;
    int tranposeCOL = preTrainrow;

    // printf("transpose Matrix: \n");
    // print(transposeMatrix, tranposeROW, tranposeCOL);

    double *multiplyMatrix = multiply(transposeMatrix, tranposeROW, tranposeCOL,
                                      matrix, preTrainrow, preTrainCol);
    int multiplyROW = tranposeROW;
    int multiplyCOL = preTrainCol;

    //printing multiply
    // printf("\n\nmultiply Matrix in parenthesis: \n");
    // print(multiplyMatrix, multiplyROW, multiplyCOL);

    double **inverseMatrix = inverse(multiplyMatrix, multiplyROW, multiplyCOL);
    //turn double pointer into single pointer
    double *inverseMatrixIn1D = calloc(multiplyROW * multiplyCOL, sizeof(double *));
    int start = 0;
    for (int row = 0; row < multiplyROW; row++)
    {
        for (int col = 0; col < multiplyCOL; col++)
        {
            inverseMatrixIn1D[start] = inverseMatrix[row][col];
            start++;
        }
    }

    //printing inverse
    // printf("\ninverse Matrix: \n");
    // print(inverseMatrixIn1D, multiplyROW, multiplyCOL);

    double *firstMultiply = multiply(inverseMatrixIn1D, multiplyROW, multiplyCOL, transposeMatrix, tranposeROW, tranposeCOL);
    //firstmultply
    //row = multiplyrow;
    //col = tranposeCol

    // printf("\nmultiply between inverse and tranpose: \n");
    // print(firstMultiply, multiplyROW, tranposeCOL);

    double *secondMultiply = multiply(firstMultiply, multiplyROW, tranposeCOL, yTrainMatrix, preTrainrow, 1);
    //row = multiplyrow
    //col = 1
    // printf("\nsecond multiply: row: %d col %d\n", multiplyROW, 1);
    // print(secondMultiply, multiplyROW, 1);




  
    // printf("\nINPUT MATRIX\n");
    // print(changeInput, inputRow, inputCol);
    // input * secondmultiply
    double *finalAnswer = multiply(changeInput, inputRow, inputCol, secondMultiply, multiplyROW, 1);

   
    
    for(int i = 0; i < inputRow; i++){
        printf("%.0f\n",finalAnswer[i]);
    }



    free(finalAnswer);
    free(secondMultiply);
    free(firstMultiply);
    free_matrix(inverseMatrix,multiplyROW);
    free(inverseMatrixIn1D);
    free(multiplyMatrix);
    free(transposeMatrix);
    free(changeInput);
    free(inputMatrix);
    free(matrix);
    free(preMatrix);
    free(yTrainMatrix);
    free(fileTrain);
    free(file);

    fclose(training);
    fclose(input);
    return EXIT_SUCCESS;
    
}








