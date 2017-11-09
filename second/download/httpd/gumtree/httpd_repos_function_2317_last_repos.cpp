static apr_status_t ififo_pull(h2_ififo *fifo, int *pi, int block)
{
    apr_status_t rv;
    
    if (fifo->aborted) {
        return APR_EOF;
    }
    
    if ((rv = apr_thread_mutex_lock(fifo->lock)) == APR_SUCCESS) {
        rv = ipull_head(fifo, pi, block);
        apr_thread_mutex_unlock(fifo->lock);
    }
    return rv;
}