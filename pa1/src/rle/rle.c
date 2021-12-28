#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char *compress(char *input)
{   
    int indexLength;
    size_t lengthOfSentence = strlen(input) * 2;
    size_t memSize = lengthOfSentence + 1;
    
    char *compressString = NULL;
    compressString = calloc(memSize, sizeof(char));

    char *numOfChars = NULL;
    numOfChars = calloc(memSize, sizeof(char));

    
    int second = 0;
    int lenOfInput = strlen(input);

    for (int i = 0; i < lenOfInput; i++)
    {
        if (isdigit(input[i]))
        {
            printf("error\n");
            free(numOfChars);
            free(compressString);
            return "";
        }
        indexLength = 1;
        compressString[second++] = input[i];

        while (input[i] == input[i + 1] && i + 1 < lenOfInput)
        {
            i++;
            indexLength++;
        }
        //putting in the int into the int array
        sprintf(numOfChars, "%d", indexLength);

        //putting the num in int arry to the answer
        for (int k = 0; *(numOfChars + k);second++, k++)
        {
            compressString[second] = numOfChars[k];
        }
    }
    //must add terminating char
    compressString[second] = '\0';
    free(numOfChars);
    return compressString;
}

int main(int argc, char *argv[])
{
    char *input;
    input = argv[1];

    //loose end testcases
    if (input == NULL || strlen(input) == 0 )
    {
        return EXIT_SUCCESS;
    }else if(strcmp(input, " ") == 0){
        return EXIT_SUCCESS;
    }

    char *answer = compress(input);

    //if it is "" it means that it contains a digit
    if (strcmp(answer, "") == 0)
    {
        return EXIT_SUCCESS;
    } //if the compress string is greater than the input string
    else if (strlen(answer) > strlen(input))
    {
        free(answer);
        printf("%s\n", input);

        return EXIT_SUCCESS;
    }
    else //normal path
    {
        printf("%s\n", answer);
        free(answer);

        return EXIT_SUCCESS;
    }
}