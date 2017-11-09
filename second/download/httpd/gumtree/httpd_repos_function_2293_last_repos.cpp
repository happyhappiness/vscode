apr_status_t h2_fifo_try_push(h2_fifo *fifo, void *elem)
{
    return fifo_push(fifo, elem, 0);
}