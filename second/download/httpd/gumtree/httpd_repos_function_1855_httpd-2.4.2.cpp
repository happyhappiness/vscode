static apr_status_t connection_constructor(void **resource, void *params,
                                           apr_pool_t *pool)
{
    apr_pool_t *ctx;
    apr_pool_t *scpool;
    proxy_conn_rec *conn;
    proxy_worker *worker = (proxy_worker *)params;

    /*
     * Create the subpool for each connection
     * This keeps the memory consumption constant
     * when disconnecting from backend.
     */
    apr_pool_create(&ctx, pool);
    apr_pool_tag(ctx, "proxy_conn_pool");
    /*
     * Create another subpool that manages the data for the
     * socket and the connection member of the proxy_conn_rec struct as we
     * destroy this data more frequently than other data in the proxy_conn_rec
     * struct like hostname and addr (at least in the case where we have
     * keepalive connections that timed out).
     */
    apr_pool_create(&scpool, ctx);
    apr_pool_tag(scpool, "proxy_conn_scpool");
    conn = apr_pcalloc(ctx, sizeof(proxy_conn_rec));

    conn->pool   = ctx;
    conn->scpool = scpool;
    conn->worker = worker;
    conn->inreslist = 1;
    *resource = conn;

    return APR_SUCCESS;
}