static int noloris_post(apr_pool_t *pconf, apr_pool_t *ptmp, apr_pool_t *plog,
                        server_rec *s)
{
    apr_status_t rv;
    int max_bans = thread_limit * server_limit / default_max_connections;
    shm_size = ADDR_MAX_SIZE * max_bans;

    rv = apr_shm_create(&shm, shm_size, NULL, pconf);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                     "Failed to create shm segment; mod_noloris disabled");
        apr_hash_clear(trusted);
        shm = NULL;
    }
    return 0;
}