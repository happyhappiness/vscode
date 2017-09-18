    }

    /* 
     * Create the pool of worker threads
     */
    ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf, 
                 "Child %d: Starting %d worker threads.", my_pid, nthreads);
    child_handles = (thread) alloca(nthreads * sizeof(int));
    for (i = 0; i < nthreads; i++) {
        ap_update_child_status_from_indexes(0, i, SERVER_STARTING, 
                                            (request_rec *) NULL);
        child_handles[i] = (thread) _beginthreadex(NULL, 0, (LPTHREAD_START_ROUTINE) worker_main,
                                                   (void *) i, 0, &tid);
    }

    /* 
     * Start the accept thread
     */
    if (osver.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
        _beginthreadex(NULL, 0, (LPTHREAD_START_ROUTINE) win9x_accept,
                       (void *) i, 0, &tid);
    } else {
        /* Start an accept thread per listener */
        SOCKET nlsd; /* native listening sock descriptor */
        ap_listen_rec *lr;
        for (lr = ap_listeners; lr; lr = lr->next) {
            if (lr->sd != NULL) {
                apr_os_sock_get(&nlsd, lr->sd);
                _beginthreadex(NULL, 1000, (LPTHREAD_START_ROUTINE) winnt_accept,
                               (void *) nlsd, 0, &tid);
            }
        }
    }

    /* Wait for one of three events:
     * exit_event: 
     *    The exit_event is signaled by the parent process to notify 
     *    the child that it is time to exit.
