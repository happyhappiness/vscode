        }
    }
    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r, 
                  "link_reverse_map %s --> %s", s, ctx.s);
    return ctx.s;
}

/*******************************************************************************
 * FIFO queue
 ******************************************************************************/

struct h2_proxy_fifo {
    void **elems;
    int nelems;
    int set;
    int head;
    int count;
    int aborted;
    apr_thread_mutex_t *lock;
    apr_thread_cond_t  *not_empty;
    apr_thread_cond_t  *not_full;
};

static int nth_index(h2_proxy_fifo *fifo, int n) 
{
    return (fifo->head + n) % fifo->nelems;
}

static apr_status_t fifo_destroy(void *data) 
{
    h2_proxy_fifo *fifo = data;

    apr_thread_cond_destroy(fifo->not_empty);
    apr_thread_cond_destroy(fifo->not_full);
    apr_thread_mutex_destroy(fifo->lock);

    return APR_SUCCESS;
}

static int index_of(h2_proxy_fifo *fifo, void *elem)
{
    int i;
    
    for (i = 0; i < fifo->count; ++i) {
        if (elem == fifo->elems[nth_index(fifo, i)]) {
            return i;
        }
    }
    return -1;
}

static apr_status_t create_int(h2_proxy_fifo **pfifo, apr_pool_t *pool, 
                               int capacity, int as_set)
{
    apr_status_t rv;
    h2_proxy_fifo *fifo;
    
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

apr_status_t h2_proxy_fifo_create(h2_proxy_fifo **pfifo, apr_pool_t *pool, int capacity)
{
    return create_int(pfifo, pool, capacity, 0);
}

apr_status_t h2_proxy_fifo_set_create(h2_proxy_fifo **pfifo, apr_pool_t *pool, int capacity)
{
    return create_int(pfifo, pool, capacity, 1);
}

apr_status_t h2_proxy_fifo_term(h2_proxy_fifo *fifo)
{
    apr_status_t rv;
    if ((rv = apr_thread_mutex_lock(fifo->lock)) == APR_SUCCESS) {
        fifo->aborted = 1;
        apr_thread_mutex_unlock(fifo->lock);
    }
    return rv;
}

apr_status_t h2_proxy_fifo_interrupt(h2_proxy_fifo *fifo)
{
    apr_status_t rv;
    if ((rv = apr_thread_mutex_lock(fifo->lock)) == APR_SUCCESS) {
        apr_thread_cond_broadcast(fifo->not_empty);
        apr_thread_cond_broadcast(fifo->not_full);
        apr_thread_mutex_unlock(fifo->lock);
    }
    return rv;
}

int h2_proxy_fifo_count(h2_proxy_fifo *fifo)
{
    return fifo->count;
}

int h2_proxy_fifo_capacity(h2_proxy_fifo *fifo)
{
    return fifo->nelems;
}

static apr_status_t check_not_empty(h2_proxy_fifo *fifo, int block)
{
    if (fifo->count == 0) {
        if (!block) {
            return APR_EAGAIN;
        }
        while (fifo->count == 0) {
            if (fifo->aborted) {
                return APR_EOF;
            }
            apr_thread_cond_wait(fifo->not_empty, fifo->lock);
        }
    }
    return APR_SUCCESS;
}

static apr_status_t fifo_push(h2_proxy_fifo *fifo, void *elem, int block)
{
    apr_status_t rv;
    
    if (fifo->aborted) {
        return APR_EOF;
    }

    if ((rv = apr_thread_mutex_lock(fifo->lock)) == APR_SUCCESS) {
        if (fifo->set && index_of(fifo, elem) >= 0) {
            /* set mode, elem already member */
            apr_thread_mutex_unlock(fifo->lock);
            return APR_EEXIST;
        }
        else if (fifo->count == fifo->nelems) {
            if (block) {
                while (fifo->count == fifo->nelems) {
                    if (fifo->aborted) {
                        apr_thread_mutex_unlock(fifo->lock);
                        return APR_EOF;
                    }
                    apr_thread_cond_wait(fifo->not_full, fifo->lock);
                }
            }
            else {
                apr_thread_mutex_unlock(fifo->lock);
                return APR_EAGAIN;
            }
        }
        
        ap_assert(fifo->count < fifo->nelems);
        fifo->elems[nth_index(fifo, fifo->count)] = elem;
        ++fifo->count;
        if (fifo->count == 1) {
            apr_thread_cond_broadcast(fifo->not_empty);
        }
        apr_thread_mutex_unlock(fifo->lock);
    }
    return rv;
}

apr_status_t h2_proxy_fifo_push(h2_proxy_fifo *fifo, void *elem)
{
    return fifo_push(fifo, elem, 1);
}

apr_status_t h2_proxy_fifo_try_push(h2_proxy_fifo *fifo, void *elem)
{
    return fifo_push(fifo, elem, 0);
}

static void *pull_head(h2_proxy_fifo *fifo)
{
    void *elem;
    
    ap_assert(fifo->count > 0);
    elem = fifo->elems[fifo->head];
    --fifo->count;
    if (fifo->count > 0) {
        fifo->head = nth_index(fifo, 1);
        if (fifo->count+1 == fifo->nelems) {
            apr_thread_cond_broadcast(fifo->not_full);
        }
    }
    return elem;
}

static apr_status_t fifo_pull(h2_proxy_fifo *fifo, void **pelem, int block)
{
    apr_status_t rv;
    
    if (fifo->aborted) {
        return APR_EOF;
    }
    
    if ((rv = apr_thread_mutex_lock(fifo->lock)) == APR_SUCCESS) {
        if ((rv = check_not_empty(fifo, block)) != APR_SUCCESS) {
            apr_thread_mutex_unlock(fifo->lock);
            *pelem = NULL;
            return rv;
        }

        ap_assert(fifo->count > 0);
        *pelem = pull_head(fifo);

        apr_thread_mutex_unlock(fifo->lock);
    }
    return rv;
}

apr_status_t h2_proxy_fifo_pull(h2_proxy_fifo *fifo, void **pelem)
{
    return fifo_pull(fifo, pelem, 1);
}

apr_status_t h2_proxy_fifo_try_pull(h2_proxy_fifo *fifo, void **pelem)
{
    return fifo_pull(fifo, pelem, 0);
}

apr_status_t h2_proxy_fifo_remove(h2_proxy_fifo *fifo, void *elem)
{
    apr_status_t rv;
    
    if (fifo->aborted) {
        return APR_EOF;
    }

    if ((rv = apr_thread_mutex_lock(fifo->lock)) == APR_SUCCESS) {
        int i, rc;
        void *e;
        
        rc = 0;
        for (i = 0; i < fifo->count; ++i) {
            e = fifo->elems[nth_index(fifo, i)];
            if (e == elem) {
                ++rc;
            }
            else if (rc) {
                fifo->elems[nth_index(fifo, i-rc)] = e;
            }
        }
        if (rc) {
            fifo->count -= rc;
            if (fifo->count + rc == fifo->nelems) {
                apr_thread_cond_broadcast(fifo->not_full);
            }
            rv = APR_SUCCESS;
        }
        else {
            rv = APR_EAGAIN;
        }
        
        apr_thread_mutex_unlock(fifo->lock);
    }
    return rv;
}
