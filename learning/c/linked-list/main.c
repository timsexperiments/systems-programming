#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node *next;
    int value;
} node;

typedef void (*list_callback)(struct node *, void *args);

struct list
{
    struct node *head;
    struct node *tail;
};

struct list *list_init();
void list_free(struct list);
void list_add(struct list *, int value);
void list_remove(struct list *, int search_value);
void list_pop_queue(struct list *);
void list_pop_stack(struct list *);
struct node *node_init();
void list_print(struct list);
void list_foreach(struct list, list_callback callback, void *args);

int main()
{
    // Test empty list initialization
    struct list *list = list_init();
    list_print(*list);

    // Test removing from empty list
    list_remove(list, 4);
    list_print(*list);

    // Test popping from empty list
    list_pop_queue(list);
    list_print(*list);
    list_pop_stack(list);
    list_print(*list);

    // Test adding and removing single element
    list_add(list, 4);
    list_print(*list);
    list_remove(list, 4);
    list_print(*list);

    // Test adding and popping single element
    list_add(list, 4);
    list_print(*list);
    list_pop_queue(list);
    list_print(*list);
    list_add(list, 4);
    list_print(*list);
    list_pop_stack(list);
    list_print(*list);

    // Test adding and removing multiple elements
    list_add(list, 4);
    list_add(list, 6);
    list_add(list, 3);
    list_add(list, 8);
    list_add(list, 0);
    list_add(list, 3);
    list_add(list, 4);
    list_print(*list);
    list_remove(list, 3);
    list_print(*list);
    list_remove(list, 4);
    list_print(*list);
    list_remove(list, 4);
    list_print(*list);

    // Test popping entire list
    list_pop_queue(list);
    list_pop_queue(list);
    list_pop_queue(list);
    list_pop_queue(list);
    list_pop_queue(list);
    list_pop_queue(list);
    list_pop_queue(list);
    list_print(*list);

    // Test freeing list
    list_free(*list);
    free(list);
}

struct list *list_init()
{
    struct list *list = malloc(sizeof(struct list));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void node_free(struct node *);
void list_free(struct list list)
{
    node_free(list.head);
}

void node_free(struct node *node)
{
    if (node == NULL)
    {
        return;
    }
    if (node->next != NULL)
    {
        node_free(node->next);
        node->next = NULL;
    }
    free(node);
    node = NULL;
}

struct node *node_init()
{
    struct node *node = malloc(sizeof(struct node));
    node->next = NULL;
    return node;
}

void list_add(struct list *list, int value)
{
    struct node *node = node_init();
    node->value = value;
    if (list->head == NULL && list->tail == NULL)
    {
        list->head = node;
        if (list->tail != NULL)
        {
            node_free(list->tail);
            list->tail = NULL;
        }
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        list->tail = node;
    }
}

void list_pop_stack(struct list *list)
{
    if (list->head == list->tail)
    {
        struct node *old_head = list->head;
        list->head = NULL;
        list->tail = NULL;
        node_free(old_head);
    }
    if (list->head == NULL)
    {
        return;
    }
    struct node *old_head = list->head;
    list->head = list->head->next;
    old_head->next = NULL;
    node_free(old_head);
    old_head = NULL;
}

struct node_remove_next_args
{
    int num_removed;
    int search_value;
};
void node_remove_next(struct node *, void *);
void list_remove(struct list *list, int search_value)
{
    if (list->head == NULL)
    {
        return;
    }
    if (list->head->value == search_value)
    {
        struct node *old_head = list->head;
        if (list->head == list->tail)
        {
            list->tail = NULL;
        }
        list->head = list->head->next;
        old_head->next = NULL;
        node_free(old_head);
        old_head = NULL;
        return;
    }
    struct node_remove_next_args *args = malloc(sizeof(struct node_remove_next_args));
    args->num_removed = 0;
    args->search_value = search_value;
    list_foreach(*list, node_remove_next, (void *)args);
    free(args);
    args = NULL;
}

void list_pop_queue_recursive(struct node *node);
void list_pop_queue(struct list *list)
{
    if (list->head == list->tail)
    {
        struct node *old_head = list->head;
        list->head = NULL;
        list->tail = NULL;
        node_free(old_head);
        return;
    }
    list_pop_queue_recursive(list->head);
}
void list_pop_queue_recursive(struct node *node)
{
    if (node == NULL)
    {
        return;
    }
    if (node->next == NULL)
    {
        return;
    }
    if (node->next->next == NULL)
    {
        struct node *node_to_remove = node->next;
        node->next = NULL;
        node_free(node_to_remove);
        node_to_remove = NULL;
    }
}

void node_remove_next(struct node *node, void *args)
{
    struct node_remove_next_args *options = (struct node_remove_next_args *)args;
    if (options->num_removed > 0)
    {
        return;
    }
    if (options == NULL)
    {
        return;
    }
    if (node == NULL)
    {
        return;
    }
    if (node->next == NULL)
    {
        return;
    }
    if (node->next->value == options->search_value)
    {
        struct node *node_to_remove = node->next;
        node->next = node->next->next;
        node_to_remove->next = NULL;
        node_free(node_to_remove);
        options->num_removed++;
    }
}

void node_print(struct node *, void *args);
void list_print(struct list list)
{
    printf("list{ head = %p, tail = %p }[", list.head, list.tail);
    list_foreach(list, node_print, NULL);
    printf("]\n");
}

void node_print(struct node *node, void *args)
{
    printf("{ value = %d, next = %p }", node->value, node->next);
    if (node->next != NULL)
    {
        printf(", ");
    }
}

void list_foreach_recursive(struct node *current, list_callback callback, void *args);
void list_foreach(struct list list, list_callback callback, void *args)
{
    list_foreach_recursive(list.head, callback, args);
}

void list_foreach_recursive(struct node *current, list_callback callback, void *args)
{
    if (current == NULL)
    {
        return;
    }
    callback(current, args);
    list_foreach_recursive(current->next, callback, args);
}