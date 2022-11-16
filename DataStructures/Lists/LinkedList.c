#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

struct Node * create_node_ll(void *data, int size);
void destroy_node_ll(struct Node *node_to_destroy);

struct Node * iterate_ll(struct LinkedList *linked_list, int index);
void insert_ll(struct LinkedList *linked_list, int index, void *data, int size);
void remove_node_ll(struct LinkedList *linked_list, int index);
void * retrieve_ll(struct LinkedList *linked_list, int index);

struct LinkedList linked_list_constructor()
{
    struct LinkedList new_list;
    new_list.head = NULL;
    new_list.length = 0;

    new_list.insert = insert_ll;
    new_list.remove = remove_node_ll;
    new_list.retrieve = retrieve_ll;
    
    return new_list;
}

void linked_list_destructor(struct LinkedList *linked_list)
{
    for (int i = 0; i < linked_list->length; i++)
    {
        linked_list->remove(linked_list, 0);
    }
}

struct Node * create_node_ll(void *data, int size)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    *new_node = node_constructor(data, size);
    return new_node;
}

void destroy_node_ll(struct Node *node_to_destoy)
{
    node_destructor(node_to_destoy);
}

struct Node * iterate_ll(struct LinkedList *linked_list, int index)
{
    if (index < 0 || index >= linked_list->length)
    {
        return NULL;
    }
    struct Node *cursor = linked_list->head;
    for (int i = 0; i<index; i++)
    {
        cursor = cursor->next;
    }
    return cursor;
}

void insert_ll(struct LinkedList *linked_list, int index, void *data, int size)
{
    struct Node *node_to_insert = create_node_ll(data, size);
    if (index == 0)
    {
        node_to_insert->next = linked_list->head;
        linked_list->head = node_to_insert;
    }
    else
    {
        struct Node *cursor = iterate_ll(linked_list, index - 1);
        node_to_insert->next = cursor->next;
        cursor->next = node_to_insert;
    }
    linked_list->length += 1;
}

void remove_node_ll(struct LinkedList *linked_list, int index)
{
    if (index == 0)
    {
        struct Node *node_to_remove = linked_list->head;
        linked_list->head = node_to_remove->next;
        destroy_node_ll(node_to_remove);
    }
    else
    {
        struct Node *cursor = iterate_ll(linked_list, index-1);
        struct Node *node_to_remove = cursor->next;
        cursor->next = node_to_remove->next;
        destroy_node_ll(node_to_remove);
    }
    linked_list->length -= 1;
}

void* retrieve_ll(struct LinkedList *linked_list, int index)
{
    struct Node *cursor = iterate_ll(linked_list, index);
    if (cursor)
        return cursor->data;
    else
        return NULL;
}