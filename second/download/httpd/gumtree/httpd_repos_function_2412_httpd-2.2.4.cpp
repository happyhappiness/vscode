apr_status_t ap_queue_init(fd_queue_t * queue, int queue_capacity,
                           apr_pool_t * a)
{
    int i;
    apr_status_t rv;

    if ((rv = apr_thread_mutex_create(&queue->one_big_mutex,
                                      APR_THREAD_MUTEX_DEFAULT,
                                      a)) != APR_SUCCESS) {
        return rv;
    }
    if ((rv = apr_thread_cond_create(&queue->not_empty, a)) != APR_SUCCESS) {
        return rv;
    }

    queue->data = apr_palloc(a, queue_capacity * sizeof(fd_queue_elem_t));
    queue->bounds = queue_capacity;
    queue->nelts = 0;

    /* Set all the sockets in the queue to NULL */
    for (i = 0; i < queue_capacity; ++i)
        queue->data[i].sd = NULL;

    apr_pool_cleanup_register(a, queue, ap_queue_destroy,
                              apr_pool_cleanup_null);

    return APR_SUCCESS;
}