#ifndef LinkedList_h
#define LinkedList_h

#include "../Common/Node.h"

/*Struct LinkedList is a collection of Nodes, where each node points to the next one.
Used in Queue and Dictionary. Allocates memory for Nodes.*/
struct LinkedList
{
    //Pointer to the first node in chain.
    struct Node *head;
    //Number of nodes in the chain.
    int length;

    // LinkedList functions
    void (*insert)(struct LinkedList *linked_list, int index, void *data, int size);
    void (*remove)(struct LinkedList *linked_list, int index);
    void * (*retrieve)(struct LinkedList *linked_list, int index);
};

struct LinkedList linked_list_constructor(void);
// linked_list_destructor free all the allocated memory
void linked_list_destructor(struct LinkedList *linked_list);

#endif