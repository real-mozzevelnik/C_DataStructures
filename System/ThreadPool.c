#include "ThreadPool.h"
#include <stdlib.h>

void * thread_job(void *arg);

struct ThreadPool thread_pool_constructor(int num_threads)
{
    struct ThreadPool thread_pool;

    thread_pool.num_threads = num_threads;
    thread_pool.active = 1;
    thread_pool.pool = (pthread_t*)malloc(sizeof(pthread_t)*num_threads);
    for (int i = 0; i < num_threads; i++)
    {
        pthread_create(&thread_pool.pool[i], NULL, thread_job, NULL);
    }
    thread_pool.work = queue_constructor();

    thread_pool.lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;

    thread_pool.signal = (pthread_cond_t)PTHREAD_COND_INITIALIZER;

    return thread_pool;
}

void * thread_job(void *arg)
{
    struct ThreadPool *thread_pool = (struct ThreadPool*)arg;
    while (thread_pool->active == 1)
    {
        pthread_mutex_lock(&thread_pool->lock);
        struct ThreadJob job = *(struct ThreadJob*)thread_pool->work.peek(&thread_pool->work);
        thread_pool->work.pop(&thread_pool->work);
        pthread_mutex_unlock(&thread_pool->lock);
    }
}