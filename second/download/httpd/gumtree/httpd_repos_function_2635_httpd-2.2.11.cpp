static apr_status_t ms_find_conn(apr_memcache_server_t *ms, apr_memcache_conn_t **conn) 
{
#if APR_HAS_THREADS
    return apr_reslist_acquire(ms->conns, (void **)conn);
#else
    *conn = ms->conn;
    return APR_SUCCESS;
#endif
}