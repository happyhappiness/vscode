static void authn_cache_child_init(apr_pool_t *p, server_rec *s)
{
    const char *lock = apr_global_mutex_lockfile(authn_cache_mutex);
    apr_status_t rv;
    if (!configured) {
        return;       /* don't waste the overhead of creating mutex & cache */
    }
    rv = apr_global_mutex_child_init(&authn_cache_mutex, lock, p);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                     "failed to initialise mutex in child_init");
    }
}