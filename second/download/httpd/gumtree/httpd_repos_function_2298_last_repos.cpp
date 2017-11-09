static apr_status_t fifo_peek(h2_fifo *fifo, h2_fifo_peek_fn *fn, void *ctx, int block)
{
    apr_status_t rv;
    void *elem;
    
    if (fifo->aborted) {
        return APR_EOF;
    }
    
    if (APR_SUCCESS == (rv = apr_thread_mutex_lock(fifo->lock))) {
        if (APR_SUCCESS == (rv = pull_head(fifo, &elem, block))) {
            switch (fn(elem, ctx)) {
                case H2_FIFO_OP_PULL:
                    break;
                case H2_FIFO_OP_REPUSH:
                    rv = fifo_push_int(fifo, elem, block);
                    break;
            }
        }
        apr_thread_mutex_unlock(fifo->lock);
    }
    return rv;
}