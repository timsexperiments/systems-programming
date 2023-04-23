#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *sentence = NULL;
    int size = 10;
    int c;
    sentence = calloc(size + 1, sizeof(char));
    sentence[size] = '\0';

    printf("Tell me anything: ");
    while ((c = getchar()) != '\n')
    {
        if (sentence == NULL || size == strlen(sentence))
        {
            int length = strlen(sentence);
            size *= 2;
            sentence = realloc(sentence, size + 1);
            memset(sentence + length, 0, (size - length) * sizeof(char));
            sentence[size] = '\0';
        }
        sentence[strlen(sentence)] = c;
    }

    sentence[strlen(sentence)] = '\0';
    printf("You said: %s\n", sentence);
    free(sentence);
    return 0;
}