    }

    /* Always return the SUCCESS */
    return APR_SUCCESS;
}

/* reslist constructor */
static apr_status_t connection_constructor(void **resource, void *params,
                                           apr_pool_t *pool)
{
    apr_pool_t *ctx;
    proxy_conn_rec *conn;
    proxy_worker *worker = (proxy_worker *)params;

    /*
     * Create the subpool for each connection
     * This keeps the memory consumption constant
     * when disconnecting from backend.
     */
    apr_pool_create(&ctx, pool);
    conn = apr_pcalloc(pool, sizeof(proxy_conn_rec));

    conn->pool   = ctx;
    conn->worker = worker;
#if APR_HAS_THREADS
    conn->inreslist = 1;
#endif
    *resource = conn;

