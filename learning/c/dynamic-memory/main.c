#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vector
{
  int size;
  int *data;
  int capacity;
};

struct vector vector_init();
int push_back(struct vector *v, int value);
int remove_item(struct vector *v, const int index);
int *get(struct vector v, const int index);
void print_vector(struct vector v);
void free_vector(struct vector v);

int main()
{
  struct vector v = vector_init();
  printf("Initialized empty vector.\n");
  print_vector(v);
  printf("\n");

  push_back(&v, 1);
  printf("Added 1 to vector.\n");
  print_vector(v);
  printf("\n");

  push_back(&v, 2);
  printf("Added 2 to vector.\n");
  print_vector(v);
  printf("\n");

  push_back(&v, 3);
  printf("Added 3 to vector.\n");
  print_vector(v);
  printf("\n");

  push_back(&v, 4);
  printf("Added 4 to vector.\n");
  print_vector(v);
  printf("\n");

  push_back(&v, 5);
  printf("Added 5 to vector.\n");
  print_vector(v);
  printf("\n");

  int *item = get(v, 0);
  printf("Got item at index 0: %d\n", *item);
  print_vector(v);
  printf("\n");

  item = get(v, 2);
  printf("Got item at index 2: %d\n", *item);
  print_vector(v);
  printf("\n");

  remove_item(&v, 2);
  printf("Removed item at index 2.\n");
  print_vector(v);
  printf("\n");

  remove_item(&v, 0);
  printf("Removed item at index 0.\n");
  print_vector(v);
  printf("\n");

  item = get(v, 1);
  printf("Got item at index 1: %d\n", *item);
  print_vector(v);
  printf("\n");

  remove_item(&v, 0);
  printf("Removed item at index 0.\n");
  print_vector(v);
  printf("\n");

  remove_item(&v, 0);
  printf("Removed item at index 0.\n");
  print_vector(v);
  printf("\n");

  item = get(v, 0);
  if (item == NULL)
  {
    printf("Got invalid item at index 0.\n");
  }
  else
  {
    printf("Got item at index 0: %d\n", *item);
  }
  print_vector(v);
  printf("\n");

  remove_item(&v, 0);
  printf("Removed item at index 0.\n");
  print_vector(v);
  printf("\n");

  remove_item(&v, 0);
  printf("Removed item at index 0.\n");
  print_vector(v);
  printf("\n");

  free_vector(v);
  printf("Freed memory used by vector.\n");

  return 0;
}

struct vector vector_init()
{
  struct vector vector = {.data = NULL, .size = 0, .capacity = 0};
  return vector;
}

int push_back(struct vector *v, int value)
{
  // Invalid - Size should never be larger than the capacity.
  if (v->size > v->capacity)
  {
    return 0;
  }

  // Resize if full.
  if (v->size == v->capacity)
  {
    int capacity = v->capacity + 10;
    int *data = (int *)(malloc(capacity * sizeof(int)));
    if (data == NULL)
    {
      return 0;
    }
    bzero(data, capacity);
    memcpy(data, v->data, v->capacity * sizeof(int));
    free(v->data);
    v->data = data;
    v->capacity = capacity;
  }

  // Add the new value to the data.
  v->data[v->size] = value;
  v->size++;
  return 1;
}

int remove_item(struct vector *v, const int index)
{
  if (v->size == 0 || index >= v->size)
  {
    printf("Index %d is out of range.\n", index);
    return 0;
  }
  for (int i = index; i < v->size; i++)
  {
    v->data[i] = v->data[i + 1];
  }
  v->size--;
  return 1;
}

int *get(struct vector v, const int index)
{
  if (index < 0 || index > v.size)
  {
    printf("Index %d is out of range.\n", index);
    return NULL;
  }
  return &v.data[index];
}

void print_vector(struct vector v)
{
  printf("vector{ size = %d, data = [", v.size);
  for (int current_value = 0; current_value < v.size; current_value++)
  {
    printf("%d", v.data[current_value]);
    if (current_value != v.size - 1)
    {
      printf(", ");
    }
  }
  printf("], capacity = %d }\n", v.capacity);
}

void free_vector(struct vector v)
{
  if (v.data != NULL)
  {
    free(v.data);
  }
  v.data = NULL;
}