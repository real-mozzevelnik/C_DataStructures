#include "Dictionary.h"
#include <stdlib.h>
#include <string.h>

// Recursive function to destroy every node in dict.
void recursive_dictionary_destroy(struct Node *cursor);

void insert_dict(struct Dictionary *dictionary, void *key, int key_size, void *value, int value_size);
void * search_dict(struct Dictionary *dictionary, void *key, int key_size);

struct Dictionary dictionary_constructor(int (*compare)(void *key_one, void *key_two))
{
    // Init dictionary.
    struct Dictionary dictionary;
    dictionary.binary_search_tree = binary_search_tree_constructor(compare);
    dictionary.keys = linked_list_constructor();
    dictionary.insert = insert_dict;
    dictionary.search = search_dict;

    return dictionary;
}

// Destroys linked list that contains all the keys, and all of the node in dict.
void dictionary_destructor(struct Dictionary *dictionary)
{
    linked_list_destructor(&dictionary->keys);
    recursive_dictionary_destroy(dictionary->binary_search_tree.head);
}

// Recursive destroy of every node and entry.
void recursive_dictionary_destroy(struct Node *cursor)
{
    // If there is previous node, delete it first.
    if (cursor->previous)
    {
        recursive_dictionary_destroy(cursor->previous);
    }
    // If there is next node, delete it first.
    if (cursor->next)
    {
        recursive_dictionary_destroy(cursor->next);
    }
    // After all next and previous nodes are destroyed, destroy entry in actual node and actual node.
    entry_destructor((struct Entry *)cursor->data);
    free(cursor);
}
#include<stdio.h>
void * search_dict(struct Dictionary *dictionary, void *key, int key_size)
{
    // As we are searching in tree, we need some entry to compare with.
    // That's why there is need in random dummy value and construction new entry.
    int dummy_value = 0; 
    struct Entry searcheble = entry_constructor(key, key_size, &dummy_value, sizeof(dummy_value));
    void * result = dictionary->binary_search_tree.search(&dictionary->binary_search_tree, &searcheble);
    // entry_destructor(&searcheble); 
    if (result)
    {
        return ((struct Entry *)result)->value;
    }
    else
    {
        return NULL;
    }
}

void insert_dict(struct Dictionary *dictionary, void *key, int key_size, void *value, int value_size)
{
    // Constructs new entry with given data, inserts it in tree and inserts the key in linked list of keys.
    struct Entry entry = entry_constructor(key, key_size, value, value_size);
    dictionary->binary_search_tree.insert(&dictionary->binary_search_tree, &entry, sizeof(entry));
    dictionary->keys.insert(&dictionary->keys, dictionary->keys.length, key, key_size);
}

// If there is previous node, delete it first.
// todo: rewrite that shitty.
int compare_string_keys(void *entry_one, void *entry_two)
{
    if (strcmp((char*)(((struct Entry*)entry_one)->key), (char*)(((struct Entry*)entry_two)->key)) > 0)
    {
        return 1;
    }
    else if (strcmp((char*)(((struct Entry*)entry_one)->key), (char*)(((struct Entry*)entry_two)->key)) < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}