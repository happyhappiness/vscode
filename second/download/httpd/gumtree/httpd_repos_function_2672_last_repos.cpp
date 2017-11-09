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