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
