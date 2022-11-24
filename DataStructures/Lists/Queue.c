#include "Queue.h"

//Actually uses the linked list functions.

// Adds new node to the end of the Queue.
void push(struct Queue *queue, void *data, int size)
{
    queue->list.insert(&queue->list, queue->list.length, data, size);
}

// Retrieve first node data.
void * peek(struct Queue *queue)
{
    void *data = queue->list.retrieve(&queue->list, 0);
    return data;
}

// Removes first node from the Queue
void pop(struct Queue *queue)
{
    queue->list.remove(&queue->list, 0);
}

struct Queue queue_constructor(void)
{
    struct Queue queue;
    queue.list = linked_list_constructor();

    queue.push = push;
    queue.peek = peek;
    queue.pop = pop;
    
    return queue;
};

void queue_destructor(struct Queue *queue)
{
    linked_list_destructor(&queue->list);
}