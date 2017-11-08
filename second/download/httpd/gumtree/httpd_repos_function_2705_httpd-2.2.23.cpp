static apr_status_t
mc_conn_construct(void **conn_, void *params, apr_pool_t *pool)
{
    apr_status_t rv = APR_SUCCESS;
    apr_memcache_conn_t *conn;
    apr_pool_t *np;
    apr_pool_t *tp;
    apr_memcache_server_t *ms = params;

    rv = apr_pool_create(&np, pool);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    rv = apr_pool_create(&tp, np);
    if (rv != APR_SUCCESS) {
        apr_pool_destroy(np);
        return rv;
    }

    conn = apr_palloc(np, sizeof( apr_memcache_conn_t ));

    conn->p = np;
    conn->tp = tp;

    rv = apr_socket_create(&conn->sock, APR_INET, SOCK_STREAM, 0, np);

    if (rv != APR_SUCCESS) {
        apr_pool_destroy(np);
        return rv;
    }

    conn->buffer = apr_palloc(conn->p, BUFFER_SIZE);
    conn->blen = 0;
    conn->ms = ms;

    rv = conn_connect(conn);
    if (rv != APR_SUCCESS) {
        apr_pool_destroy(np);
    }
    else {
        *conn_ = conn;
    }
    
    return rv;
}