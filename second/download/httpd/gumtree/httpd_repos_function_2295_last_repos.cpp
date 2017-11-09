static apr_status_t fifo_pull(h2_fifo *fifo, void **pelem, int block)
{
    apr_status_t rv;
    
    if (fifo->aborted) {
        return APR_EOF;
    }
    
    if ((rv = apr_thread_mutex_lock(fifo->lock)) == APR_SUCCESS) {
        rv = pull_head(fifo, pelem, block);
        apr_thread_mutex_unlock(fifo->lock);
    }
    return rv;
}