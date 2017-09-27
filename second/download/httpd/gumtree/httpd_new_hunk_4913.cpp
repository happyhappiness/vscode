        if (ResetEvent(restart_event) == 0) {
            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), s, APLOGNO(00425)
                         "Parent: ResetEvent(restart_event) failed.");
        }
        if (SetEvent(child_exit_event) == 0) {
            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), s, APLOGNO(00426)
                         "Parent: SetEvent for child process event %pp failed.",
                         event_handles[CHILD_HANDLE]);
        }
        /* Don't wait to verify that the child process really exits,
         * just move on with the restart.
         */
        CloseHandle(event_handles[CHILD_HANDLE]);
