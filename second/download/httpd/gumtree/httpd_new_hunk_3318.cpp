    apr_status_t rv;
    int i;
    int threads_created = 0;
    int listener_started = 0;
    int loops;
    int prev_threads_created;
    int max_recycled_pools = -1;

    /* We must create the fd queues before we start up the listener
     * and worker threads. */
    worker_queue = apr_pcalloc(pchild, sizeof(*worker_queue));
    rv = ap_queue_init(worker_queue, threads_per_child, pchild);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, rv, ap_server_conf,
                     "ap_queue_init() failed");
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    if (ap_max_mem_free != APR_ALLOCATOR_MAX_FREE_UNLIMITED) {
        /* If we want to conserve memory, let's not keep an unlimited number of
         * pools & allocators.
         * XXX: This should probably be a separate config directive
         */
        max_recycled_pools = threads_per_child * 3 / 4 ;
    }
    rv = ap_queue_info_create(&worker_queue_info, pchild,
                              threads_per_child, max_recycled_pools);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, rv, ap_server_conf,
                     "ap_queue_info_create() failed");
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    /* Create the timeout mutex and main pollset before the listener
     * thread starts.
     */
    rv = apr_thread_mutex_create(&timeout_mutex, APR_THREAD_MUTEX_DEFAULT,
                                 pchild);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                     "creation of the timeout mutex failed.");
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    /* Create the main pollset */
    rv = apr_pollset_create(&event_pollset,
                            threads_per_child, /* XXX don't we need more, to handle
                                                * connections in K-A or lingering
                                                * close?
                                                */
                            pchild, APR_POLLSET_THREADSAFE | APR_POLLSET_NOCOPY);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                     "apr_pollset_create with Thread Safety failed.");
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    worker_sockets = apr_pcalloc(pchild, threads_per_child
                                 * sizeof(apr_socket_t *));

    loops = prev_threads_created = 0;
    while (1) {
        /* threads_per_child does not include the listener thread */
