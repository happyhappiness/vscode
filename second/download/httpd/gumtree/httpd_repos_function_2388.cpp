static int noloris_pre(apr_pool_t *pconf, apr_pool_t *ptmp, apr_pool_t *plog)
{
    ap_mpm_query(AP_MPMQ_HARD_LIMIT_THREADS, &thread_limit);
    ap_mpm_query(AP_MPMQ_HARD_LIMIT_DAEMONS, &server_limit);

    /* set up default config stuff here */
    trusted = apr_hash_make(pconf);
    default_max_connections = 50;
    recheck_time = apr_time_from_sec(10);
    return 0;
}