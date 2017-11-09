apr_status_t h2_fifo_pull(h2_fifo *fifo, void **pelem)
{
    return fifo_pull(fifo, pelem, 1);
}