apr_status_t h2_ififo_create(h2_ififo **pfifo, apr_pool_t *pool, int capacity)
{
    return icreate_int(pfifo, pool, capacity, 0);
}