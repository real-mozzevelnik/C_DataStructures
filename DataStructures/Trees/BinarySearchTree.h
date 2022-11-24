#ifndef BinarySearchTree_h
#define BinarySearchTree_h

#include "../Common/Node.h"

/*Struct BinarySearchTree is a collection of nodes, where each one node points to no more than two subnodes.
Subnode with data value less than the main node are stored to the left(prrevious), with bigger data - to the right(next).
Uses memory allocation.*/

struct BinarySearchTree
{
    struct Node *head;

    // Required funcion to compare elements of tree.
    int (*compare)(void *data_one, void *data_two);
    // Finds required data from tree.
    void * (*search)(struct BinarySearchTree *tree, void *data);
    // Adds new node to the tree.
    void (*insert)(struct BinarySearchTree *tree, void *data, int size);
};

//Counstructor takes function as an argument to compare items in tree. 
struct BinarySearchTree binary_search_tree_constructor(int (*compare)(void *data_one, void *data_two));
// Free allocated memory.
void binary_search_tree_destructor(struct BinarySearchTree tree);

// Prototips of compare functions. Not done yet cause not required for me.
int binary_search_tree_int_compare(void *data_one, void *data_two);
int binary_search_tree_float_compare(void *data_one, void *data_two);
int binary_search_tree_char_compare(void *data_one, void *data_two);
//Done
int binary_search_tree_str_compare(void *data_one, void *data_two);

#endif