#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node *next;
    struct node *prev;
    int value;
} node;

typedef void (*list_callback)(struct node *, void *args);

struct list
{
    struct node **head;
    struct node **tail;
};

struct list *list_init();
void list_push_stack(struct list *l, int value);
void list_push_queue(struct list *l, int value);
void node_print(struct node *node, void *);
void list_print(struct list *l);
void list_destack(struct list *l, int *val);
void list_dequeue(struct list *l, int *val);
void node_disconnect(struct node *node, int *val);
void list_remove(struct list *l, int value, int *val);
void list_foreach(struct list *l, list_callback callback, void *args);
void list_free(struct list *l);
void node_free(struct node *node);

int main()
{
    // Initialize a new list
    printf("Initializing list...\n");
    struct list *l = list_init();
    printf("List: ");
    list_print(l);
    printf("\n");

    // Push some elements onto the stack
    printf("Pushing elements onto the stack...\n");
    list_push_stack(l, 1);
    list_push_stack(l, 2);
    list_push_stack(l, 3);
    printf("List: ");
    list_print(l);
    printf("\n");

    // Push some elements onto the queue
    printf("Pushing elements onto the queue...\n");
    list_push_queue(l, 4);
    list_push_queue(l, 5);
    list_push_queue(l, 6);
    printf("List: ");
    list_print(l);
    printf("\n");

    // Dequeue some elements from the queue
    printf("Dequeueing elements from the queue...\n");
    int *val1 = malloc(sizeof(int));
    list_dequeue(l, val1);
    int *val2 = malloc(sizeof(int));
    list_dequeue(l, val2);
    int *val3 = malloc(sizeof(int));
    list_dequeue(l, val3);
    printf("Dequeued values: %d, %d, %d\n", *val1, *val2, *val3);
    printf("List: ");
    list_print(l);
    printf("\n");

    // Destack some elements from the stack
    printf("Destacking some elements from the stack...\n");
    int *val4 = malloc(sizeof(int));
    list_destack(l, val4);
    int *val5 = malloc(sizeof(int));
    list_destack(l, val5);
    printf("Dequeued values: %d, %d\n", *val4, *val5);
    printf("List: ");
    list_print(l);
    printf("\n");

    // Remove an element from the list
    printf("Removing an element from the list...\n");
    int *removed_val = malloc(sizeof(int));
    list_remove(l, 2, removed_val);
    printf("Removed value: %p\n", removed_val);
    printf("List: ");
    list_print(l);
    printf("\n");

    // Free the list
    printf("Freeing the list...\n");
    list_free(l);
    printf("List: ");
    list_print(l);
    printf("\n");
    free(l);
    free(val1);
    free(val2);
    free(val3);
    free(val4);
    free(val5);
    free(removed_val);
    return 0;
}

struct list *list_init()
{
    struct list *l = malloc(sizeof(struct list));
    l->head = malloc(sizeof(struct node *));
    l->tail = malloc(sizeof(struct node *));
    *l->head = NULL;
    *l->tail = NULL;
    return l;
}

void list_push_stack(struct list *l, int value)
{
    struct node *node = malloc(sizeof(struct node));
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    if (*l->head == NULL)
    {
        *l->tail = node;
    }
    else
    {
        node->next = *l->head;
        (*l->head)->prev = node;
    }
    *l->head = node;
}

void list_push_queue(struct list *l, int value)
{
    struct node *node = malloc(sizeof(struct node));
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    if (l->tail == NULL)
    {
        *l->head = node;
    }
    else
    {
        node->prev = *l->tail;
        (*l->tail)->next = node;
    }
    *l->tail = node;
}

void list_destack(struct list *l, int *val)
{
    struct node *head = *l->head;
    if (head == NULL)
    {
        val = NULL;
        return;
    }
    head->next->prev = NULL;
    l->head = head->next;
    head->next = NULL;
    *val = head->value;
    node_free(head);
}

void list_dequeue(struct list *l, int *val)
{
    struct node *tail = l->tail;
    if (tail == NULL)
    {
        val = NULL;
        return;
    }
    tail->prev->next = NULL;
    *l->tail = tail->prev;
    tail->prev = NULL;
    *val = tail->value;
    free(tail);
}

void node_print(struct node *node, void *args)
{
    printf("%d", node->value);
    if (node->next != NULL)
    {
        printf(", ");
    }
}

void list_print(struct list *l)
{
    printf("[");
    list_foreach(l, node_print, NULL);
    printf("]\n");
}

void list_free(struct list *l)
{
    if (l->head == NULL)
    {
        return;
    }
    if (*l->head != NULL)
    {
        node_free(*l->head);
        (*l->head) = NULL;
        (*l->tail) = NULL;
    }
    if (l->head != NULL)
    {
        free(l->head);
        l->head = NULL;
    }
    if (l->tail != NULL)
    {
        free(l->tail);
        l->tail = NULL;
    }
}

void node_free(struct node *node)
{
    if (node == NULL)
    {
        return;
    }
    if (node->prev != NULL)
    {
        node_free(node->next);
    }
    if (node->prev != NULL)
    {
        node_free(node->prev);
    }
    if (node != NULL)
    {
        free(node);
        node = NULL;
    }
}

void node_to_end(struct node *node, list_callback callback, void *args);
void list_foreach(struct list *l, list_callback callback, void *args)
{
    if (l->head != NULL)
    {
        node_to_end(*l->head, callback, args);
    }
}
void node_to_end(struct node *node, list_callback callback, void *args)
{
    if (node != NULL)
    {
        callback(node, args);
        node_to_end(node->next, callback, (void *)args);
    }
}

void node_disconnect(struct node *node, int *val)
{
    if (node == NULL)
    {
        val = NULL;
        return;
    }
    *val = node->value;
    if (node->prev != NULL)
    {
        node->prev->next = node->next;
    }
    if (node->next != NULL)
    {
        node->next->prev = node->prev;
    }
    node->next = NULL;
    node->prev = NULL;
    node_free(node);
}

struct check_value_args
{
    int **value;
    int matches;
    int search_val;
};

void node_remove_check(struct node *node, void *args);
void list_remove(struct list *l, int value, int *val)
{
    struct check_value_args *args = malloc(sizeof(struct check_value_args));
    args->value = malloc(sizeof(int *));
    *args->value = val;
    args->matches = 0;
    args->search_val = value;
    list_foreach(l, node_remove_check, (void *)args);
    printf("Found %d matches\n", args->matches);
    free(args->value);
    args->value = NULL;
    free(args);
    args = NULL;
}
void node_remove_check(struct node *node, void *args)
{
    struct check_value_args *options = (struct check_value_args *)args;
    if (node == NULL)
    {
        return;
    }

    if (options == NULL)
    {
        return;
    }

    if (options->matches != 0)
    {
        return;
    }

    if (options->search_val == node->value)
    {
        printf("DISCONNECTING....\n");
        node_disconnect(node, *options->value);
        options->matches++;
    }
}