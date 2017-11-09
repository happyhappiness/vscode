apr_status_t h2_proxy_fifo_set_create(h2_proxy_fifo **pfifo, apr_pool_t *pool, int capacity)
{
    return create_int(pfifo, pool, capacity, 1);
}