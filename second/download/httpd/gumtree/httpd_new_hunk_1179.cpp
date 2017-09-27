/**
 * Configuration and start-up
 */
static int mem_cache_post_config(apr_pool_t *p, apr_pool_t *plog,
                                 apr_pool_t *ptemp, server_rec *s)
{
    /* Sanity check the cache configuration */
    if (sconf->min_cache_object_size >= sconf->max_cache_object_size) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s,
                     "MCacheMaxObjectSize must be greater than MCacheMinObjectSize");
        return DONE;
    }
