#include "BinarySearchTree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Functions to create Node in tree.
struct Node * create_node_bst(void *data, int size);
void destroy_node_bst(struct Node *node_to_destroy);

// Recursive functions. Dangerous.
struct Node * iterate_bst(struct BinarySearchTree *tree, struct Node *cursor, void *data, int *direction);
void recursive_tree_destructor(struct Node *node);

// Functions which are we accessed from .h file.
void * search_bst(struct BinarySearchTree *tree, void *data);
void insert_bst(struct BinarySearchTree *tree, void *data, int size);

struct BinarySearchTree binary_search_tree_constructor(int (*compare)(void *data_one, void *data_two))
{
    // Init tree.
    struct BinarySearchTree tree;
    tree.head = NULL;
    tree.compare = compare;
    tree.search = search_bst;
    tree.insert = insert_bst;

    return tree;
}

// todo: change parametr from tree to tree pointer. 
void binary_search_tree_destructor(struct BinarySearchTree tree)
{
    recursive_tree_destructor(tree.head);
}

// Creates node. Uses memory allocation.
struct Node * create_node_bst(void *data, int size)
{
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
    *new_node = node_constructor(data, size);
    return new_node;
}

// Destroys node.
void destroy_node_bst(struct Node *node_to_destoy)
{
    node_destructor(node_to_destoy);
}

// Recursive function that iterates data in tree.
struct Node * iterate_bst(struct BinarySearchTree *tree, struct Node *cursor, void *data, int *direction)
{
    // Compares data in cursor and given data.
    // If it equals 1, our data is bigger.
    // If it's -1, our data is less.
    // If it's 0, our data equals to actual node data.
    if (tree->compare(cursor->data, data) == 1)
    {
        // Continue searching if there is next node, else our direction is 1.
        if (cursor->next)
        {
            return iterate_bst(tree, cursor->next, data, direction);
        }
        else
        {
            *direction = 1;
            return cursor;
        }
    }
    else if (tree->compare(cursor->data, data) == -1)
    {
        // Continue searching if there is previous node, else our direction is -1.
        if (cursor->previous)
        {
            return iterate_bst(tree, cursor->previous, data, direction);
        }
        else
        {
            *direction = -1;
            return cursor;
        }
    }
    else
    {
        *direction = 0;
        return cursor;
    }
}

// Recursive function that destroy every single node in tree.
void recursive_tree_destructor(struct Node *node)
{
    // If there is next node, destroy it first.
    if (node->previous)
    {
        recursive_tree_destructor(node->previous);

    }
    // If there is previous node, destroy it first.
    if (node->next)
    {
        recursive_tree_destructor(node->next);
    }
    // Destroy actual node after we destroyed all the next and previous nodes.
    destroy_node_bst(node);
}

// Finds required data and returns it.
// If there is no such data, returns NULL.
void * search_bst(struct BinarySearchTree *tree, void *data)
{
    int direction = 0;
    struct Node *cursor = iterate_bst(tree, tree->head, data, &direction);
    if (direction == 0)
    {
        return cursor->data;
    }
    else
    {
        return NULL;
    }
}

// Creates new node, finds the rigth place for it and inserts it.
void insert_bst(struct BinarySearchTree *tree, void *data, int size)
{
    // If there is no head in tree, create the head.
    if (!tree->head)
    {
        tree->head = create_node_bst(data, size);
    }
    // Finds the right place by value of direction that changes in iterate function.
    else
    {
        int direction = 0;
        struct Node *cursor = iterate_bst(tree, tree->head, data, &direction);

        if (direction == 1)
        {
            cursor->next = create_node_bst(data, size);
        }
        else if (direction == -1)
        {
            cursor->previous = create_node_bst(data, size);
        }
    }
}

// Function to compare strings in tree
// todo: rewrite this shit, it's awful.
int binary_search_tree_str_compare(void *data_one, void *data_two)
{
    int comparison = strcmp(data_one, data_two);
    
    if (comparison > 0)
    {
        return 1;
    }
    else if (comparison < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}