static apr_status_t ms_find_conn(apr_memcache_server_t *ms, apr_memcache_conn_t **conn) 
{
    apr_status_t rv;
    apr_bucket_alloc_t *balloc;
    apr_bucket *e;

#if APR_HAS_THREADS
    rv = apr_reslist_acquire(ms->conns, (void **)conn);
#else
    *conn = ms->conn;
    rv = APR_SUCCESS;
#endif

    if (rv != APR_SUCCESS) {
        return rv;
    }

    balloc = apr_bucket_alloc_create((*conn)->tp);
    (*conn)->bb = apr_brigade_create((*conn)->tp, balloc);
    (*conn)->tb = apr_brigade_create((*conn)->tp, balloc);

    e = apr_bucket_socket_create((*conn)->sock, balloc);
    APR_BRIGADE_INSERT_TAIL((*conn)->bb, e);

    return rv;
}