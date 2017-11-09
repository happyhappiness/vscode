static apr_status_t create_int(h2_fifo **pfifo, apr_pool_t *pool, 
                               int capacity, int as_set)
{
    apr_status_t rv;
    h2_fifo *fifo;
    
    fifo = apr_pcalloc(pool, sizeof(*fifo));
    if (fifo == NULL) {
        return APR_ENOMEM;
    }

    rv = apr_thread_mutex_create(&fifo->lock,
                                 APR_THREAD_MUTEX_UNNESTED, pool);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    rv = apr_thread_cond_create(&fifo->not_empty, pool);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    rv = apr_thread_cond_create(&fifo->not_full, pool);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    fifo->elems = apr_pcalloc(pool, capacity * sizeof(void*));
    if (fifo->elems == NULL) {
        return APR_ENOMEM;
    }
    fifo->nelems = capacity;
    fifo->set = as_set;
    
    *pfifo = fifo;
    apr_pool_cleanup_register(pool, fifo, fifo_destroy, apr_pool_cleanup_null);

    return APR_SUCCESS;
}