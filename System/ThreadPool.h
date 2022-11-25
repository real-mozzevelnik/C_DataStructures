#ifndef ThreadPool_h
#define ThreadPool_h

#include "../DataStructures/Lists/Queue.h"
#include <pthread.h>

struct ThreadPool
{
    int num_threads;
    int active;
    struct Queue work;
    pthread_t *pool;
    pthread_mutex_t lock;
    pthread_cond_t signal;
};

struct ThreadJob
{
    void * (*job)(void *arg);
    void *arg;
};

struct ThreadPool thread_pool_constructor(int num_threads);
struct ThreadJob thread_job_constructor(void * (*job)(void *arg), void *arg);

#endif