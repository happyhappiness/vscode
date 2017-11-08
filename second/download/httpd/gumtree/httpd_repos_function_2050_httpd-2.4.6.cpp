static apr_status_t connection_destructor(void *resource, void *params,
                                          apr_pool_t *pool)
{
    proxy_conn_rec *conn = (proxy_conn_rec *)resource;

    /* Destroy the pool only if not called from reslist_destroy */
    if (conn->worker->cp->pool) {
        apr_pool_destroy(conn->pool);
    }

    return APR_SUCCESS;
}