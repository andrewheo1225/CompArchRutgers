#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *sentence;
    sentence = argv[1];
    size_t lengthOfSentence = strlen(sentence);
    size_t sz_mem = lengthOfSentence + 1;
    char *stack = NULL;
    stack = calloc(sz_mem, sizeof(char));

    int stackIndex = 0;
    char delimiter[] = "({[]})";
    int requiresOpen = 1; //1->true, 0->false
    char empty[] = "";
    int stringisBalance = 1;

    for (int i = 0; i < lengthOfSentence; i++)
    {
        //check if nondelimter characters are there
        if (isalpha(sentence[i]) != 0)
        {
            continue;
        }
        //opening brackets
        if (sentence[i] == delimiter[0])
        { // (
            stack[stackIndex] = sentence[i];
            stackIndex++;
        }
        else if (sentence[i] == delimiter[1])
        { // {
            stack[stackIndex] = sentence[i];
            stackIndex++;
        }
        else if (sentence[i] == delimiter[2])
        { // [
            stack[stackIndex] = sentence[i];
            stackIndex++;
        }
        else
        {
            int stackBefore = stackIndex - 1;

            //closing brackets
            if (sentence[i] == delimiter[5])
            { //   )

                if (strlen(stack) == 0)
                { //empty stack
                    printf("%d: %c\n", i, sentence[i]);
                    requiresOpen = 0;
                    stringisBalance = 0;
                    free(stack);
                    return EXIT_FAILURE;
                }
                else if (stack[stackBefore] != delimiter[0])
                { //unexpected delimiter
                    printf("%d: %c\n", i, sentence[i]);
                    requiresOpen = 0;
                    stringisBalance = 0;
                    free(stack);
                    return EXIT_FAILURE;
                }
                else
                {
                    stackIndex--;
                    stack[stackIndex] = empty[0];
                }
            }
            else if (sentence[i] == delimiter[4])
            { //  }
                if (strlen(stack) == 0)
                { //empty stack
                    printf("%d: %c\n", i, sentence[i]);
                    requiresOpen = 0;
                    stringisBalance = 0;
                    free(stack);
                    return EXIT_FAILURE;
                }
                else if (stack[stackBefore] != delimiter[1])
                { //unexpected delimiter
                    printf("%d: %c\n", i, sentence[i]);
                    requiresOpen = 0;
                    stringisBalance = 0;
                    free(stack);
                    return EXIT_FAILURE;
                }
                else
                {
                    stackIndex--;
                    stack[stackIndex] = empty[0];
                }
            }
            else if (sentence[i] == delimiter[3])
            { //   ]
                if (strlen(stack) == 0)
                { //empty stack
                    printf("%d: %c\n", i, sentence[i]);
                    requiresOpen = 0;
                    stringisBalance = 0;
                    free(stack);
                    return EXIT_FAILURE;
                }
                else if (stack[stackBefore] != delimiter[2])
                { //unexpected delimiter
                    printf("%d: %c\n", i, sentence[i]);
                    requiresOpen = 0;
                    stringisBalance = 0;
                    free(stack);
                    return EXIT_FAILURE;
                }
                else
                {
                    stackIndex--;
                    stack[stackIndex] = empty[0];
                }
            }
        }
    }
    //perfect balance
    if (stringisBalance == 1 && stackIndex == 0)
    {   
        free(stack);
        return EXIT_SUCCESS;
    }
    //finding closing delimiter for open parenthesis
    if (requiresOpen == 1 && stackIndex > 0)
    {
        char *open;
        size_t length = strlen(stack);
        size_t sz_mem = length + 1;
        open = calloc(sz_mem, sizeof(char));
        int openIndex = 0;
        stackIndex--;
        while (stackIndex > -1)
        {
            if (stack[stackIndex] == delimiter[0])
            { //(
                open[openIndex] = delimiter[5];
                openIndex++;

                stackIndex--;
            }
            else if (stack[stackIndex] == delimiter[1])
            { //{
                open[openIndex] = delimiter[4];
                openIndex++;
                stackIndex--;
            }
            else if (stack[stackIndex] == delimiter[2])
            { //[

                open[openIndex] = delimiter[3];
                openIndex++;
                stackIndex--;
            }
        }

        printf("open: ");
        for (int i = 0; i < strlen(open); i++)
        {
            printf("%c", open[i]);
        }
        printf("\n");
        free(stack);
        free(open);
        return EXIT_FAILURE;
    }

    free(stack);
}