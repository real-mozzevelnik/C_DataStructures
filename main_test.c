#include <stdio.h>
#include <stdlib.h>
#include "DataStructures/Lists/LinkedList.h"

int cmp(void *a, void *b)
{
    int *x = a;
    int *y = b;
    if (*x > *y)
        return 1;

    else
        return -11;
}

int main()
{
    struct LinkedList list = linked_list_constructor();
    for (int i = 10; i > 0; i--)
    {
        list.insert(&list, 10-i, &i, sizeof(i));
    }
    list.sort(&list, cmp);
    for (int i = 0; i <10; i++)
    {
        printf("%d\n", *(int*)list.retrieve(&list, i));
    }
    return 0;
}

