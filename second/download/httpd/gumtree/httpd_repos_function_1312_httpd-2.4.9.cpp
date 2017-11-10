static void socache_child_init(apr_pool_t *p, server_rec *s)
{
    const char *lock;
    apr_status_t rv;
    if (!socache_mutex) {
        return; /* don't waste the overhead of creating mutex & cache */
    }
    lock = apr_global_mutex_lockfile(socache_mutex);
    rv = apr_global_mutex_child_init(&socache_mutex, lock, p);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(02394)
                "failed to initialise mutex in child_init");
    }
}