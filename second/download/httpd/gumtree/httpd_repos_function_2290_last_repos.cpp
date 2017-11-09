static apr_status_t fifo_push_int(h2_fifo *fifo, void *elem, int block)
{
    if (fifo->aborted) {
        return APR_EOF;
    }

    if (fifo->set && index_of(fifo, elem) >= 0) {
        /* set mode, elem already member */
        return APR_EEXIST;
    }
    else if (fifo->count == fifo->nelems) {
        if (block) {
            while (fifo->count == fifo->nelems) {
                if (fifo->aborted) {
                    return APR_EOF;
                }
                apr_thread_cond_wait(fifo->not_full, fifo->lock);
            }
        }
        else {
            return APR_EAGAIN;
        }
    }
    
    ap_assert(fifo->count < fifo->nelems);
    fifo->elems[nth_index(fifo, fifo->count)] = elem;
    ++fifo->count;
    if (fifo->count == 1) {
        apr_thread_cond_broadcast(fifo->not_empty);
    }
    return APR_SUCCESS;
}