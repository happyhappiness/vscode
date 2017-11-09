static apr_status_t check_not_empty(h2_proxy_fifo *fifo, int block)
{
    if (fifo->count == 0) {
        if (!block) {
            return APR_EAGAIN;
        }
        while (fifo->count == 0) {
            if (fifo->aborted) {
                return APR_EOF;
            }
            apr_thread_cond_wait(fifo->not_empty, fifo->lock);
        }
    }
    return APR_SUCCESS;
}