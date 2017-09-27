                                                    0,
                                                    0); /* CONCURRENT ACTIVE THREADS */
        apr_thread_mutex_create(&qlock, APR_THREAD_MUTEX_DEFAULT, pchild);
        qwait_event = CreateEvent(NULL, TRUE, FALSE, NULL);
        if (!qwait_event) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                         "Child %lu: Failed to create a qwait event.", my_pid);
            exit(APEXIT_CHILDINIT);
        }
    }

    /*
     * Create the pool of worker threads
     */
    ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                 "Child %lu: Starting %d worker threads.", my_pid, ap_threads_per_child);
    child_handles = (HANDLE) apr_pcalloc(pchild, ap_threads_per_child * sizeof(HANDLE));
    apr_thread_mutex_create(&child_lock, APR_THREAD_MUTEX_DEFAULT, pchild);

    while (1) {
        for (i = 0; i < ap_threads_per_child; i++) {
            int *score_idx;
