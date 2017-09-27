                 "Child %d: Acquired the start mutex.", my_pid);

    /*
     * Create the worker thread dispatch IOCompletionPort
     * on Windows NT/2000
     */
    if (osver.dwPlatformId != VER_PLATFORM_WIN32_WINDOWS) {
        /* Create the worker thread dispatch IOCP */
        ThreadDispatchIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE,
                                                    NULL,
                                                    0,
                                                    0); /* CONCURRENT ACTIVE THREADS */
        apr_thread_mutex_create(&qlock, APR_THREAD_MUTEX_DEFAULT, pchild);
    }

    /* 
     * Create the pool of worker threads
     */
    ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf, 
