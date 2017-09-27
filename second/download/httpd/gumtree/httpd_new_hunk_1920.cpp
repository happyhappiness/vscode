     * restarts, so we'll create a global pool and never clean it.
     */
    rv = apr_pool_create(&global_pool, NULL);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                     "Fatal error: unable to create global pool "
                     "for use by the scoreboard");
        return rv;
    }

    /* The config says to create a name-based shmem */
    if (ap_scoreboard_fname) {
        /* make sure it's an absolute pathname */
