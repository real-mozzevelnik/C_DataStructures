#ifndef Queue_h
#define Queue_h

#include "LinkedList.h"

/*Struct Queue is a version of LinkedList, where data
always be added to the end and removed from the front.*/

struct Queue
{
    //Embedding ll.
    struct LinkedList list;

    //Add new item to the end.
    void (*push)(struct Queue *queue, void *data, int size);
    //Retrieve first item data.
    void * (*peek)(struct Queue *queue);
    //Remove first item.
    void (*pop)(struct Queue *queue);
};

struct Queue queue_constructor(void);
void queue_destructor(struct Queue *queue);

#endif