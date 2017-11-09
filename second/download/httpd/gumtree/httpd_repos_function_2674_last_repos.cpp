apr_status_t h2_proxy_fifo_try_pull(h2_proxy_fifo *fifo, void **pelem)
{
    return fifo_pull(fifo, pelem, 0);
}