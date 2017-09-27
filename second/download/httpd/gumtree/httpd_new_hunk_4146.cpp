         */
        max_recycled_pools = threads_per_child * 3 / 4 ;
    }
    rv = ap_queue_info_create(&worker_queue_info, pchild,
                              threads_per_child, max_recycled_pools);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, rv, ap_server_conf, APLOGNO(03101)
                     "ap_queue_info_create() failed");
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    /* Create the timeout mutex and main pollset before the listener
     * thread starts.
     */
    rv = apr_thread_mutex_create(&timeout_mutex, APR_THREAD_MUTEX_DEFAULT,
                                 pchild);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf, APLOGNO(03102)
                     "creation of the timeout mutex failed.");
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    /* Create the main pollset */
    for (i = 0; i < sizeof(good_methods) / sizeof(void*); i++) {
