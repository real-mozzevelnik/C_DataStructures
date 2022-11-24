#ifndef Node_h
#define Node_h

/*Struct Node is used in Linked Lists and Binary Search Tree as a foundation.
Uses void pointers to store data cause of ability to store any data type.

Uses memory allocation to store data.
node_destructor free all the allocated memory.*/
struct Node
{
    void *data;
    struct Node *next;  // pointer to the next node in structure
    struct Node *previous; // pointer to the previous node in structure
};

// Constructor and destructor to allocate and free memory for data.
struct Node node_constructor(void *data, int size);
void node_destructor(struct Node *node);

#endif