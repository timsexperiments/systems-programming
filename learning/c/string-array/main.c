#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char wait_for_continue();
char *get_next_phrase();
char clear_input();

int main()
{
    char **all_phrases = NULL;
    int size = 1;
    all_phrases = malloc(size * sizeof(char *));
    all_phrases[size - 1] = NULL;
    char c;
    do
    {
        if (all_phrases[size - 1] != NULL)
        {
            all_phrases = realloc(all_phrases, (++size) * sizeof(char *));
            all_phrases[size - 1] = NULL;
        }
        char *current_phrase = get_next_phrase();
        all_phrases[size - 1] = current_phrase;
        c = wait_for_continue();
    } while (c == 'Y' || c == 'y');

    for (int i = 0; i < size; i++)
    {
        printf("[%p]: %s\n", all_phrases[i], all_phrases[i]);
        if (all_phrases[i] != NULL)
        {
            free(all_phrases[i]);
            all_phrases[i] = NULL;
        }
    }
    free(all_phrases);
    return 0;
}

char *get_next_phrase()
{
    char *phrase = NULL;
    int size = 10;
    int c;
    phrase = calloc(size + 1, sizeof(char));
    phrase[size] = '\0';

    printf("What would you like to say to me? ");
    while ((c = getchar()) != '\n')
    {
        if (phrase == NULL || size == strlen(phrase))
        {
            int length = strlen(phrase);
            size *= 2;
            phrase = realloc(phrase, size + 1);
            memset(phrase + length, 0, (size - length) * sizeof(char));
            phrase[size] = '\0';
        }
        phrase[strlen(phrase)] = c;
    }
    return phrase;
}

char get_answer();
char wait_for_continue()
{

    char c;
    printf("Do you have anything else to say to me (y/n)? ");
    do
    {
        c = get_answer();
    } while (c != 'n' && c != 'N' && c != 'y' && c != 'Y');
    return c;
}

char get_answer()
{
    char c = 'n';
    c = getchar();
    clear_input();
    return c;
}

char clear_input()
{
    while (getchar() != '\n')
        ;
}