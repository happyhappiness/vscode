                 "Child %d: Acquired the start mutex.", my_pid);

    /*
     * Create the worker thread dispatch IOCompletionPort
     * on Windows NT/2000
     */
    if (use_acceptex) {
        /* Create the worker thread dispatch IOCP */
        ThreadDispatchIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE,
                                                    NULL,
                                                    0,
                                                    0); /* CONCURRENT ACTIVE THREADS */
        apr_thread_mutex_create(&qlock, APR_THREAD_MUTEX_DEFAULT, pchild);
        qwait_event = CreateEvent(NULL, TRUE, FALSE, NULL);
        if (!qwait_event) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                         "Child %d: Failed to create a qwait event.", my_pid);
            exit(APEXIT_CHILDINIT);
        }
    }

    /* 
     * Create the pool of worker threads
     */
    ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf, 
