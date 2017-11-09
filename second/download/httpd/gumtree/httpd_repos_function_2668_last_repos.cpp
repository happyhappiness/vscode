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