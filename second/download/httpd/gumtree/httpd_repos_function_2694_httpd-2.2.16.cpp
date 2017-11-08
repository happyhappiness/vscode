static apr_status_t
mc_conn_destruct(void *conn_, void *params, apr_pool_t *pool)
{
    apr_memcache_conn_t *conn = (apr_memcache_conn_t*)conn_;
    
    if (conn->p) {
        apr_pool_destroy(conn->p);
    }

    free(conn); /* free non-pool space */
    
    return APR_SUCCESS;
}