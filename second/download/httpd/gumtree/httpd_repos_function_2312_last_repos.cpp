static apr_status_t ififo_push_int(h2_ififo *fifo, int id, int block)
{
    if (fifo->aborted) {
        return APR_EOF;
    }

    if (fifo->set && iindex_of(fifo, id) >= 0) {
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
    fifo->elems[inth_index(fifo, fifo->count)] = id;
    ++fifo->count;
    if (fifo->count == 1) {
        apr_thread_cond_broadcast(fifo->not_empty);
    }
    return APR_SUCCESS;
}