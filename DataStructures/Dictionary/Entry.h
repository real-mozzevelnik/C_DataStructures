#ifndef Entry_h
#define Entry_h

/*Struct Entry is the foundation of dictionary struct.
Consist of key-value pair.
Uses memory allocation to store data.*/
struct Entry
{
    void *key;
    void *value;
};

struct Entry entry_constructor(void *key, int key_size, void *value, int value_size);
// Free allocated memory.
void entry_destructor(struct Entry *entry);
#endif