#ifndef BinarySearchTree_h
#define BinarySearchTree_h

#include "../Common/Node.h"

/*Struct BinarySearchTree is a collection of nodes, whwre each one node points to no more than two subnodes.
Subnode with data value less than the main node are stored to the left(prrevious), with bigger data - to the right(next).*/


struct BinarySearchTree
{
    struct Node *head;

    int (*compare)(void *data_one, void *data_two);
    void * (*search)(struct BinarySearchTree *tree, void *data);
    void (*insert)(struct BinarySearchTree *tree, void *data, int size);
};

//Counstructor takes function as an argument to compare items in tree. 
struct BinarySearchTree binary_search_tree_constructor(int (*compare)(void *data_one, void *data_two));
void binary_search_tree_destructor(struct BinarySearchTree tree);

int binary_search_tree_int_compare(void *data_one, void *data_two);
int binary_search_tree_float_compare(void *data_one, void *data_two);
int binary_search_tree_char_compare(void *data_one, void *data_two);
int binary_search_tree_str_compare(void *data_one, void *data_two);

#endif