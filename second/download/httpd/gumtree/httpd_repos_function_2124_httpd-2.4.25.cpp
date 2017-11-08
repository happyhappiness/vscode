static apr_status_t connection_destructor(void *resource, void *params,
                                          apr_pool_t *pool)
{
    proxy_worker *worker = params;

    /* Destroy the pool only if not called from reslist_destroy */
    if (worker->cp->pool) {
        proxy_conn_rec *conn = resource;
        apr_pool_destroy(conn->pool);
    }

    return APR_SUCCESS;
}