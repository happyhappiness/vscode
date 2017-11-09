static apr_status_t fifo_push(h2_fifo *fifo, void *elem, int block)
{
    apr_status_t rv;
    
    if (fifo->aborted) {
        return APR_EOF;
    }

    if ((rv = apr_thread_mutex_lock(fifo->lock)) == APR_SUCCESS) {
        rv = fifo_push_int(fifo, elem, block);
        apr_thread_mutex_unlock(fifo->lock);
    }
    return rv;
}