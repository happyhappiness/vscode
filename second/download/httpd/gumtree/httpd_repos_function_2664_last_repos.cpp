apr_status_t h2_proxy_fifo_interrupt(h2_proxy_fifo *fifo)
{
    apr_status_t rv;
    if ((rv = apr_thread_mutex_lock(fifo->lock)) == APR_SUCCESS) {
        apr_thread_cond_broadcast(fifo->not_empty);
        apr_thread_cond_broadcast(fifo->not_full);
        apr_thread_mutex_unlock(fifo->lock);
    }
    return rv;
}