     * or global pool which spans server restarts.
     * Create our stderr_pool as a child of the plog's
     * parent pool.
     */
    apr_pool_create(&stderr_p, apr_pool_parent_get(p));
    apr_pool_tag(stderr_p, "stderr_pool");
    
    if (open_error_log(s_main, 1, stderr_p) != OK) {
        return DONE;
    }

    replace_stderr = 1;
    if (s_main->error_log) {
        apr_status_t rv;
        
        /* Replace existing stderr with new log. */
        apr_file_flush(s_main->error_log);
        rv = apr_file_dup2(stderr_log, s_main->error_log, stderr_p);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s_main,
                         "unable to replace stderr with error_log");
