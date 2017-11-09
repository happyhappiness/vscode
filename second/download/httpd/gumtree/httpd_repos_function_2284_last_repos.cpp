apr_status_t h2_fifo_create(h2_fifo **pfifo, apr_pool_t *pool, int capacity)
{
    return create_int(pfifo, pool, capacity, 0);
}