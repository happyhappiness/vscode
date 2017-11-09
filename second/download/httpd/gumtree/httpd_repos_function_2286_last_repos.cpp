apr_status_t h2_fifo_term(h2_fifo *fifo)
{
    apr_status_t rv;
    if ((rv = apr_thread_mutex_lock(fifo->lock)) == APR_SUCCESS) {
        fifo->aborted = 1;
        apr_thread_mutex_unlock(fifo->lock);
    }
    return rv;
}