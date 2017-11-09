static apr_status_t ififo_push(h2_ififo *fifo, int id, int block)
{
    apr_status_t rv;
    
    if (fifo->aborted) {
        return APR_EOF;
    }

    if ((rv = apr_thread_mutex_lock(fifo->lock)) == APR_SUCCESS) {
        rv = ififo_push_int(fifo, id, block);
        apr_thread_mutex_unlock(fifo->lock);
    }
    return rv;
}