
    /* We must create the fd queues before we start up the listener
     * and worker threads. */
    worker_queue = apr_pcalloc(pchild, sizeof(*worker_queue));
    rv = ap_queue_init(worker_queue, threads_per_child, pchild);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, rv, ap_server_conf,
                     "ap_queue_init() failed");
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    rv = ap_queue_info_create(&worker_queue_info, pchild,
                              threads_per_child);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, rv, ap_server_conf,
                     "ap_queue_info_create() failed");
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    worker_sockets = apr_pcalloc(pchild, threads_per_child
                                        * sizeof(apr_socket_t *));
