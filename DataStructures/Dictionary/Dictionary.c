#include "Dictionary.h"
#include <stdlib.h>
#include <string.h>

void insert_dict(struct Dictionary *dictionary, void *key, int key_size, void *value, int value_size);
void * search_dict(struct Dictionary *dictionary, void *key);

struct Dictionary dictionary_constructor(int (*compare)(void *key_one, void *key_two))
{
    struct Dictionary dictionary;
    dictionary.binary_search_tree = binary_search_tree_constructor(compare);
    dictionary.insert = insert_dict;
    dictionary.search = search_dict;

    return dictionary;
}

void * search_dict(struct Dictionary *dictionary, void *key)
{
    void * result = dictionary->binary_search_tree.search(&dictionary->binary_search_tree, key);
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
    struct Entry entry = entry_constructor(key, key_size, value, value_size);
    dictionary->binary_search_tree.insert(&dictionary->binary_search_tree, &entry, sizeof(entry));
}

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