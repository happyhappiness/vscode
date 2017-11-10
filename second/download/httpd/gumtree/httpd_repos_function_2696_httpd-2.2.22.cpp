static apr_status_t make_server_dead(apr_memcache_t *mc, apr_memcache_server_t *ms)
{
#if APR_HAS_THREADS
    apr_thread_mutex_lock(ms->lock);
#endif
    ms->status = APR_MC_SERVER_DEAD;
    ms->btime = apr_time_now();
#if APR_HAS_THREADS
    apr_thread_mutex_unlock(ms->lock);
#endif
    return APR_SUCCESS;
}