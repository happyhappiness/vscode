    status = apr_proc_mutex_lock(start_mutex);
    if (status != APR_SUCCESS) {
        ap_log_error(APLOG_MARK,APLOG_ERR, status, ap_server_conf,
                     "Child %d: Failed to acquire the start_mutex. Process will exit.", my_pid);
        exit(APEXIT_CHILDINIT);
    }
    ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                 "Child %d: Acquired the start mutex.", my_pid);

    /*
     * Create the worker thread dispatch IOCompletionPort
     * on Windows NT/2000
     */
