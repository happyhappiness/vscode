 * Configuration and start-up
 */
static int mem_cache_post_config(apr_pool_t *p, apr_pool_t *plog,
                                 apr_pool_t *ptemp, server_rec *s)
{
    int threaded_mpm;

    /* Sanity check the cache configuration */
    if (sconf->min_cache_object_size >= sconf->max_cache_object_size) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s,
                     "MCacheMaxObjectSize must be greater than MCacheMinObjectSize");
        return DONE;
    }
    if (sconf->max_cache_object_size >= sconf->max_cache_size) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s,
                     "MCacheSize must be greater than MCacheMaxObjectSize");
        return DONE;
    }
    ap_mpm_query(AP_MPMQ_IS_THREADED, &threaded_mpm);
    if (threaded_mpm) {
        apr_thread_mutex_create(&sconf->lock, APR_THREAD_MUTEX_DEFAULT, p);
    }

#ifdef USE_ATOMICS
