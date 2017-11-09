static apr_status_t check_not_empty(h2_fifo *fifo, int block)
{
    while (fifo->count == 0) {
        if (!block) {
            return APR_EAGAIN;
        }
        if (fifo->aborted) {
            return APR_EOF;
        }
        apr_thread_cond_wait(fifo->not_empty, fifo->lock);
    }
    return APR_SUCCESS;
}