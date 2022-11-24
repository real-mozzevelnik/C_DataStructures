#include "Node.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*Used to create node and allocate memory for data.*/
struct Node node_constructor(void *data, int size)
{
    if (size < 1)
    {
        //Checks is size is correct
        printf("Invalid data size for node...\n");
        exit(1);
    }
    struct Node node;

    //Allocate memory for data and copy it. Supports any data types.
    node.data = malloc(size);
    memcpy(node.data, data, size);

    //Intializing the pointers.
    node.next = NULL;
    node.previous = NULL;
    
    return node;
}

//Free all allocated memory.
void node_destructor(struct Node *node)
{
    free(node->data);
    free(node);
}