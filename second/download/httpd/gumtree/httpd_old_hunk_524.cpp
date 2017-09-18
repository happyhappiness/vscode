                         "restart a new child process.", my_pid);
            ap_signal_parent(SIGNAL_PARENT_RESTART);
            break;
        }
    }

    /* Setting is_graceful will cause keep-alive connections to be closed
     * rather than block on the next network read.
     */
    is_graceful = 1;

    /* Setting shutdown_in_progress prevents new connections from
     * being accepted but allows the worker threads to continue
     * handling connections that have already been accepted.
     */
    shutdown_in_progress = 1;

    /* Tell the worker threads they may exit when done handling
     * a connection.
     */
    workers_may_exit = 1;

    /* Close the listening sockets. */
    for (lr = ap_listeners; lr ; lr = lr->next) {
        apr_socket_close(lr->sd);
    }
    Sleep(1000);

    /* Release the start_mutex to let the new process (in the restart
     * scenario) a chance to begin accepting and servicing requests 
     */
    rv = apr_proc_mutex_unlock(start_mutex);
    if (rv == APR_SUCCESS) {
        ap_log_error(APLOG_MARK,APLOG_NOTICE | APLOG_NOERRNO, rv, ap_server_conf, 
                     "Child %d: Released the start mutex", my_pid);
    }
    else {
        ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf, 
                     "Child %d: Failure releasing the start mutex", my_pid);
    }

    /* Shutdown the worker threads */
    if (osver.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
        for (i = 0; i < nthreads; i++) {
            add_job(-1);
        }
    }
    else { /* Windows NT/2000 */
        /* Post worker threads blocked on the ThreadDispatch IOCompletion port */
        while (g_blocked_threads > 0) {
