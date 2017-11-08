static apr_status_t ms_release_conn(apr_memcache_server_t *ms, apr_memcache_conn_t *conn) 
{
#if APR_HAS_THREADS
    return apr_reslist_release(ms->conns, conn);
#else
    return APR_SUCCESS;
#endif
}