                     "master_main: WaitForMultipeObjects with INFINITE wait exited with WAIT_TIMEOUT");
        shutdown_pending = 1;
    }
    else if (cld == SHUTDOWN_HANDLE) {
        /* shutdown_event signalled */
        shutdown_pending = 1;
        ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, s, 
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
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, 
                     "Parent: Received restart signal -- Restarting the server.");
        if (ResetEvent(restart_event) == 0) {
            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), s,
                         "Parent: ResetEvent(restart_event) failed.");
        }
        if (SetEvent(child_exit_event) == 0) {
            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), s,
                         "Parent: SetEvent for child process %d failed.", 
                         event_handles[CHILD_HANDLE]);
        }
        /* Don't wait to verify that the child process really exits, 
         * just move on with the restart.
         */
        CloseHandle(event_handles[CHILD_HANDLE]);
        event_handles[CHILD_HANDLE] = NULL;
    }
    else {
        /* The child process exited prematurely due to a fatal error. */
        DWORD exitcode;
        if (!GetExitCodeProcess(event_handles[CHILD_HANDLE], &exitcode)) {
            /* HUH? We did exit, didn't we? */
            exitcode = APEXIT_CHILDFATAL;
        }
        if (   exitcode == APEXIT_CHILDFATAL 
            || exitcode == APEXIT_CHILDINIT
            || exitcode == APEXIT_INIT) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf, 
                         "Parent: child process exited with status %u -- Aborting.", exitcode);
        }
        else {
            int i;
            restart_pending = 1;
            ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf, 
                         "Parent: child process exited with status %u -- Restarting.", exitcode);
            for (i = 0; i < ap_threads_per_child; i++) {
                ap_update_child_status_from_indexes(0, i, SERVER_DEAD, NULL);
            }
        }
        CloseHandle(event_handles[CHILD_HANDLE]);
