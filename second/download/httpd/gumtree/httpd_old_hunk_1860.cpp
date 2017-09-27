
    /* Release the start_mutex to let the new process (in the restart
     * scenario) a chance to begin accepting and servicing requests
     */
    rv = apr_proc_mutex_unlock(start_mutex);
    if (rv == APR_SUCCESS) {
        ap_log_error(APLOG_MARK,APLOG_NOTICE, rv, ap_server_conf,
                     "Child %lu: Released the start mutex", my_pid);
    }
    else {
        ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf,
                     "Child %lu: Failure releasing the start mutex", my_pid);
    }

    /* Shutdown the worker threads */
    if (!use_acceptex) {
        for (i = 0; i < threads_created; i++) {
            add_job(INVALID_SOCKET);
        }
    }
    else { /* Windows NT/2000 */
        /* Post worker threads blocked on the ThreadDispatch IOCompletion port */
        while (g_blocked_threads > 0) {
            ap_log_error(APLOG_MARK,APLOG_INFO, APR_SUCCESS, ap_server_conf,
                         "Child %lu: %d threads blocked on the completion port", my_pid, g_blocked_threads);
            for (i=g_blocked_threads; i > 0; i--) {
                PostQueuedCompletionStatus(ThreadDispatchIOCP, 0, IOCP_SHUTDOWN, NULL);
            }
            Sleep(1000);
        }
        /* Empty the accept queue of completion contexts */
        apr_thread_mutex_lock(qlock);
        while (qhead) {
            CloseHandle(qhead->Overlapped.hEvent);
            closesocket(qhead->accept_socket);
            qhead = qhead->next;
        }
        apr_thread_mutex_unlock(qlock);
    }

    /* Give busy threads a chance to service their connections,
     * (no more than the global server timeout period which 
     * we track in msec remaining).
     */
    watch_thread = 0;
