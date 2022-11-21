#ifndef Dictionary_h
#define Dictionary_h

#include "../Trees/BinarySearchTree.h"
#include "../Lists/LinkedList.h"
#include "Entry.h"

struct Dictionary
{
    struct BinarySearchTree binary_search_tree;
    struct LinkedList keys;

    void (*insert)(struct Dictionary *dictionary, void *key, int key_size, void *value, int value_size);
    void * (*search)(struct Dictionary *dictionary, void *key, int key_size);
};

struct Dictionary dictionary_constructor(int (*compare)(void *entry_one, void *entry_two));
void dictionary_destructor(struct Dictionary *dictionary);

int compare_string_keys(void *entry_one, void *entry_two);

#endif