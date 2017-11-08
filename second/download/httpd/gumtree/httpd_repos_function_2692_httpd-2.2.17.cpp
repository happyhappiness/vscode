static apr_status_t make_server_live(apr_memcache_t *mc, apr_memcache_server_t *ms)
{
    ms->status = APR_MC_SERVER_LIVE; 
    return APR_SUCCESS;
}