#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (strlen(argv[1]) == 0 || argv[1] == NULL)
    {
        printf("\n");
    }
    else if (strcmp(argv[1], " ") == 0)
    {
        printf("\n");
    }
    else
    { //create a pointer to the second arg in stdin
        char *sentence;
        sentence = argv[1];
        int lengthOfSentence = strlen(sentence);
        for (int y = 0; y < lengthOfSentence; y++)
        {
            char word = sentence[y];
            if (islower(word))
            {
                char upperChar = toupper(sentence[y]);
                printf("%c", upperChar);
            }
            else
            {
                char reg = word;
                printf("%c", reg);
            }
        }
        printf("!!\n");
    }
    return EXIT_SUCCESS;
}
