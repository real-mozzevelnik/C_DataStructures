#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

//Functions to create and destroy nodes in linked list.
struct Node * create_node_ll(void *data, int size);
void destroy_node_ll(struct Node *node_to_destroy);

struct Node * iterate_ll(struct LinkedList *linked_list, int index);
void insert_ll(struct LinkedList *linked_list, int index, void *data, int size);
void remove_node_ll(struct LinkedList *linked_list, int index);
void * retrieve_ll(struct LinkedList *linked_list, int index);

void bubble_sort_ll(struct LinkedList *linked_list, int (*compare)(void *a, void *b));
short binary_search_ll(struct LinkedList *linked_list, void *query, int (*compare)(void *a, void *b));


struct LinkedList linked_list_constructor()
{
    // Init of struct
    struct LinkedList new_list;
    new_list.head = NULL;
    new_list.length = 0;

    new_list.insert = insert_ll;
    new_list.remove = remove_node_ll;
    new_list.retrieve = retrieve_ll;

    new_list.sort = bubble_sort_ll;
    new_list.search = binary_search_ll;
    
    return new_list;
}

//Destroys every single node in ll.
void linked_list_destructor(struct LinkedList *linked_list)
{
    for (int i = 0; i < linked_list->length; i++)
    {
        linked_list->remove(linked_list, 0);
    }
}

//Creates node. Uses memory allocation.
struct Node * create_node_ll(void *data, int size)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    *new_node = node_constructor(data, size);
    return new_node;
}

// Free node data and node itself.
void destroy_node_ll(struct Node *node_to_destoy)
{
    node_destructor(node_to_destoy);
}

// Iterates through nodes until node with required index is reached.
struct Node * iterate_ll(struct LinkedList *linked_list, int index)
{
    //Check if index is valid.
    if (index < 0 || index >= linked_list->length)
    {
        return NULL;
    }
    //Create a cursor for iteration.
    struct Node *cursor = linked_list->head;
    //Iterates until the required node is reached.
    for (int i = 0; i < index; i++)
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
        //Changing the linked list head node.
        node_to_insert->next = linked_list->head;
        linked_list->head = node_to_insert;
    }
    else
    {
        //Inserting new node.
        struct Node *cursor = iterate_ll(linked_list, index - 1);
        node_to_insert->next = cursor->next;
        cursor->next = node_to_insert;
    }
    // Increase linked list length.
    linked_list->length += 1;
}

void remove_node_ll(struct LinkedList *linked_list, int index)
{
    if (index < 0 || index >= linked_list->length)
    {
        printf("Error wit ll");
        exit(1);
    }
    if (index == 0)
    {
        //Destroy the head node.
        struct Node *node_to_remove = linked_list->head;
        // Checks if head exist.
        if (node_to_remove)
        {
            linked_list->head = node_to_remove->next;
            destroy_node_ll(node_to_remove);
        }
    }
    else
    {
        //Destroy required node.
        struct Node *cursor = iterate_ll(linked_list, index-1);
        struct Node *node_to_remove = cursor->next;
        cursor->next = node_to_remove->next;
        destroy_node_ll(node_to_remove);
    }
    // Decrease linked list length.
    linked_list->length -= 1;
}

//Finds the required node and returns it's data.
void* retrieve_ll(struct LinkedList *linked_list, int index)
{
    struct Node *cursor = iterate_ll(linked_list, index);
    if (cursor)
        return cursor->data;
    else
        return NULL;
}

void bubble_sort_ll(struct LinkedList *linked_list, int (*compare)(void *a, void *b))
{
    for (struct Node *i = iterate_ll(linked_list, 0); i; i = i->next)
    {
        for (struct Node *n = i->next; n; n = n->next)
        {
            if (compare(i->data, n->data) > 0)
            {
                void *temporary = n->data;
                n->data = i->data;
                i->data = temporary; 
            }
        }
    }
}

short binary_search_ll(struct LinkedList *linked_list, void *query, int (*compare)(void *a, void *b))
{
    int position = linked_list->length/2;
    int min_checked = 0;
    int max_checked = linked_list->length;
    while (max_checked > min_checked)
    {
        void *data = linked_list->retrieve(linked_list, position);
        if (compare(data, query) == 1)
        {
            max_checked = position;
            if (position != (min_checked + position)/2)
            {
                position = (min_checked + position)/2;
            }
            else
            {
                break;
            }
        }
        else if (compare(data, query) == -1)
        {
            min_checked = position;
            if (position != (max_checked + position)/2)
            {
                position = (max_checked + position)/2;
            }
            else
            {
                break;
            }
        }
        else
        {
            return 1;
        }
    }
    return 0;
}