static apr_status_t ififo_peek(h2_ififo *fifo, h2_ififo_peek_fn *fn, void *ctx, int block)
{
    apr_status_t rv;
    int id;
    
    if (fifo->aborted) {
        return APR_EOF;
    }
    
    if (APR_SUCCESS == (rv = apr_thread_mutex_lock(fifo->lock))) {
        if (APR_SUCCESS == (rv = ipull_head(fifo, &id, block))) {
            switch (fn(id, ctx)) {
                case H2_FIFO_OP_PULL:
                    break;
                case H2_FIFO_OP_REPUSH:
                    rv = ififo_push_int(fifo, id, block);
                    break;
            }
        }
        apr_thread_mutex_unlock(fifo->lock);
    }
    return rv;
}