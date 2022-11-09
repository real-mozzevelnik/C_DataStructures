#include "LinkedList.h"

struct Node * create_node(void *data);
void destroy_node(struct Node *node);

struct Node * iterate(int index, struct LinkedList *linked_list);
void insert_node(int index, void *data, struct LinkedList *linked_list);
void remove_node(int index, struct LinkedList *linked_list);
void* retrieve_data(int index, struct LinkedList *linked_list);

struct LinkedList linked_list_constructor()
{
    struct LinkedList new_list;
    new_list.head = NULL;
    new_list.length = 0;

    new_list.insert = insert_node;
    new_list.remove = remove_node;
    new_list.retrieve = retrieve_data;
    
    return new_list;
}

struct Node * create_node(void *data)
{
    struct Node *new_node_adress = (struct Node*)malloc(sizeof(struct Node));
    struct Node new_node_instance;
    new_node_instance.data = data;
    new_node_instance.next = NULL;
    *new_node_adress = new_node_instance;
    return new_node_adress;
}

void destroy_node(struct Node *node_to_destoy)
{
    free(node_to_destoy->data);
    free(node_to_destoy);
}

struct Node * iterate(int index, struct LinkedList *linked_list)
{
    if (index < 0 || index >= linked_list->length)
    {
        printf("index out of bound...");
        exit(9);
    }
    struct Node *cursor = linked_list->head;
    for (int i = 0; i<index; i++)
    {
        cursor = cursor->next;
    }
    return cursor;
}

void insert_node(int index, void *data, struct LinkedList *linked_list)
{
    struct Node *node_to_insert = create_node(data);
    if (index == 0)
    {
        node_to_insert->next = linked_list->head;
        linked_list->head = node_to_insert;
    }
    else
    {
        struct Node *cursor = iterate(index - 1, linked_list);
        node_to_insert->next = cursor->next;
        cursor->next = node_to_insert;
    }
    linked_list->length += 1;
}

void remove_node(int index, struct LinkedList *linked_list)
{
    if (index == 0)
    {
        struct Node *node_to_remove = linked_list->head;
        linked_list->head = node_to_remove->next;
        destroy_node(node_to_remove);
    }
    else
    {
        struct Node *cursor = iterate(index-1, linked_list);
        struct Node *node_to_remove = cursor->next;
        cursor->next = node_to_remove->next;
        destroy_node(node_to_remove);
    }
    linked_list->length -= 1;
}

void* retrieve_data(int index, struct LinkedList *linked_list)
{
    struct Node *cursor = iterate(index, linked_list);
    return cursor->data;
}