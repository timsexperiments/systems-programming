#include <stdlib.h>
#include <stdio.h>

int **create_array(int rows, int cols);
void print_array(int **arr, int rows, int cols);
void populate_array(int **arr, int rows, int cold);
void free_arr(int **arr, int rows, int cols);

int main()
{
    int rows = 0, cols = 0;
    printf("Enter a number of rows: ");
    scanf("%d", &rows);
    printf("Enter a number of columns: ");
    scanf("%d", &cols);
    int **arr = create_array(rows, cols);
    if (arr == NULL)
    {
        printf("Unable to create array.\n");
        exit(1);
    }
    populate_array(arr, rows, cols);
    print_array(arr, rows, cols);
    return 0;
}

int **create_array(int rows, int cols)
{
    if (rows == 0)
    {
        return NULL;
    }
    int **arr2d = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        arr2d[i] = malloc(cols * sizeof(int));
    }
    return arr2d;
}

void print_array(int **arr, int rows, int cols)
{
    printf("[\n");
    for (int i = 0; i < rows; i++)
    {
        printf("\t[");
        for (int j = 0; j < cols; j++)
        {
            printf("%d", arr[i][j]);
            if (cols - 1 != j)
            {
                printf(", ");
            }
        }
        printf("]");
        if (rows - 1 != i)
        {
            printf(",");
        }
        printf("\n");
    }
    printf("]\n");
}

void populate_array(int **arr, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            arr[i][j] = rand();
        }
    }
}

void free_arr(int **arr, int rows, int cols)
{
    if (arr == NULL)
    {
        return;
    }
    for (int i = 0; i < rows; i++)
    {
        if (arr[i] != NULL)
        {
            free(arr[i]);
        }
    }
    free(arr);
}
