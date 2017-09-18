                     "master_main: WaitForMultipeObjects with INFINITE wait exited with WAIT_TIMEOUT");
        shutdown_pending = 1;
    }
    else if (cld == SHUTDOWN_HANDLE) {
        /* shutdown_event signalled */
        shutdown_pending = 1;
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_NOTICE, APR_SUCCESS, s, 
                     "Parent: Received shutdown signal -- Shutting down the server.");
        if (ResetEvent(shutdown_event) == 0) {
            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), s,
                         "ResetEvent(shutdown_event)");
        }
    }
    else if (cld == RESTART_HANDLE) {
        /* Received a restart event. Prepare the restart_event to be reused 
         * then signal the child process to exit. 
         */
        restart_pending = 1;
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_NOTICE, 0, s, 
                     "Parent: Received restart signal -- Restarting the server.");
        if (ResetEvent(restart_event) == 0) {
            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), s,
                         "Parent: ResetEvent(restart_event) failed.");
        }
        if (SetEvent(child_exit_event) == 0) {
