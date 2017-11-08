apr_status_t apr_queue_create(apr_queue_t **q, 
                            int queue_capacity, 
                            apr_pool_t *a)
{
    apr_status_t rv;
    apr_queue_t *queue;
    queue = apr_palloc(a, sizeof( apr_queue_t ));
    *q = queue;

    rv = apr_thread_mutex_create(&queue->one_big_mutex,
                                 APR_THREAD_MUTEX_UNNESTED, /* nested doesn't work ;( */
                                 a);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    rv = apr_thread_cond_create(&queue->not_empty, a);
    if (rv!= APR_SUCCESS) {
        return rv;
    }

    rv = apr_thread_cond_create(&queue->not_full, a);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    /* Set all the data in the queue to NULL */
    queue->data = apr_pcalloc(a, queue_capacity * sizeof(void*));
    queue->bounds = queue_capacity;
    queue->nelts = 0;
    queue->in = 0;
    queue->out = 0;
    queue->terminated = 0;

    apr_pool_cleanup_register(a, 
                              queue, 
                              queue_destroy, 
                              apr_pool_cleanup_null);

    return APR_SUCCESS;
}