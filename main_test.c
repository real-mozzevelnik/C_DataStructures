#include <stdio.h>
#include <stdlib.h>
#include "DataStructures/Dictionary/Dictionary.h"

int cmp(void* a, void* b);

int main()
{
    struct Dictionary dict = dictionary_constructor(compare_string_keys);
    char *key = "f";
    char *key2 = "vg";
    int val = 10;
    int val2 = 11;
    dict.insert(&dict, key, sizeof(key), &val, sizeof(val));
    dict.insert(&dict, key2, sizeof(key2), &val2, sizeof(val2));
    printf("x: %d\n", *(int*)dict.search(&dict, key, sizeof(key)));
    printf("x: %d\n", *(int*)dict.search(&dict, key2, sizeof(key2)));
    dictionary_destructor(&dict);

    return 0;
}
