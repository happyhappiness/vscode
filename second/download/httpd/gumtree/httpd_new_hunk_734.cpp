    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, rv, ap_server_conf,
                     "apr_thread_create: unable to create worker thread");
        /* In case system resources are maxxed out, we don't want
           Apache running away with the CPU trying to fork over and
           over and over again if we exit. */
        apr_sleep(apr_time_from_sec(10));
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    /* If we are only running in one_process mode, we will want to
     * still handle signals. */
    if (one_process) {
