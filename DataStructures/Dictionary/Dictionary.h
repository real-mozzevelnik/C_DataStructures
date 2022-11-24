#ifndef Dictionary_h
#define Dictionary_h

#include "../Trees/BinarySearchTree.h"
#include "../Lists/LinkedList.h"
#include "Entry.h"

/*Struct Dictionary is a collection of node, each of that
contains entry with key-value pair.
Uses memory allocation.*/

struct Dictionary
{
    struct BinarySearchTree binary_search_tree;
    // Used to contain keys of all dict items.
    struct LinkedList keys;

    // Funcions to insert and search data in dict. 
    void (*insert)(struct Dictionary *dictionary, void *key, int key_size, void *value, int value_size);
    void * (*search)(struct Dictionary *dictionary, void *key, int key_size);
};

struct Dictionary dictionary_constructor(int (*compare)(void *entry_one, void *entry_two));
// Free allocated memory.
void dictionary_destructor(struct Dictionary *dictionary);

// Function to compare entrys by string values.
int compare_string_keys(void *entry_one, void *entry_two);

#endif