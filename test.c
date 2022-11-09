#include <stdio.h>
#include "DataStructures/Queue.h"

int main()
{
    struct Queue list = queue_constructor();

    for (int i = 0; i < 10; i++)
    {
        int *x = (int *)malloc(sizeof(int));
        *x = i;
        list.push(x, &list);
    }

    list.pop(&list);
    list.pop(&list);
    int *x = (int *)malloc(sizeof(int));
    *x=346;
    list.push(x, &list);

    for (int i = 0; i < 9; i++)
    {
        printf("%d\n", *(int *)list.list.retrieve(i, &list.list));
    }


    return 0;
}