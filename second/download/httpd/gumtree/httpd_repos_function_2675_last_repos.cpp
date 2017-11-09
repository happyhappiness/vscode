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