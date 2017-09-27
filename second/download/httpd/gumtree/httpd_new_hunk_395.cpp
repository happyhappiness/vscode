    /* 
     * Create the pool of worker threads
     */
    ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf, 
                 "Child %d: Starting %d worker threads.", my_pid, ap_threads_per_child);
    child_handles = (HANDLE) apr_pcalloc(pchild, ap_threads_per_child * sizeof(int));
    apr_thread_mutex_create(&child_lock, APR_THREAD_MUTEX_DEFAULT, pchild);

    while (1) {
        for (i = 0; i < ap_threads_per_child; i++) {
            int *score_idx;
            int status = ap_scoreboard_image->servers[0][i].status;
            if (status != SERVER_GRACEFUL && status != SERVER_DEAD) {
                continue;
