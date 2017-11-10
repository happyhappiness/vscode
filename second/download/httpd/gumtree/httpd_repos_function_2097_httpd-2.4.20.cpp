static void init_conn_pool(apr_pool_t *p, proxy_worker *worker)
{
    apr_pool_t *pool;
    proxy_conn_pool *cp;

    /*
     * Create a connection pool's subpool.
     * This pool is used for connection recycling.
     * Once the worker is added it is never removed but
     * it can be disabled.
     */
    apr_pool_create(&pool, p);
    apr_pool_tag(pool, "proxy_worker_cp");
    /*
     * Alloc from the same pool as worker.
     * proxy_conn_pool is permanently attached to the worker.
     */
    cp = (proxy_conn_pool *)apr_pcalloc(p, sizeof(proxy_conn_pool));
    cp->pool = pool;
    worker->cp = cp;
}