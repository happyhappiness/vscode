    /* Just use the standard apr_setup_signal_thread to block all signals
     * from being received.  The child processes no longer use signals for
     * any communication with the parent process.
     */
    rv = apr_setup_signal_thread();
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                     "Couldn't initialize signal thread");
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    if (ap_max_requests_per_child) {
        requests_this_child = ap_max_requests_per_child;
