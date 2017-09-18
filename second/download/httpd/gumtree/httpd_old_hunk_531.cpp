                ap_log_error(APLOG_MARK,APLOG_ERR, apr_get_os_error(), ap_server_conf,
                             "Parent: SetEvent for child process %d failed", event_handles[CHILD_HANDLE]);
        }
        if (event_handles[CHILD_HANDLE]) {
            rv = WaitForSingleObject(event_handles[CHILD_HANDLE], timeout);
            if (rv == WAIT_OBJECT_0) {
                ap_log_error(APLOG_MARK,APLOG_NOTICE|APLOG_NOERRNO, APR_SUCCESS, ap_server_conf,
                             "Parent: Child process exited successfully.");
                CloseHandle(event_handles[CHILD_HANDLE]);
                event_handles[CHILD_HANDLE] = NULL;
            }
            else {
                ap_log_error(APLOG_MARK,APLOG_NOTICE|APLOG_NOERRNO, APR_SUCCESS, ap_server_conf,
                             "Parent: Forcing termination of child process %d ", event_handles[CHILD_HANDLE]);
                TerminateProcess(event_handles[CHILD_HANDLE], 1);
                CloseHandle(event_handles[CHILD_HANDLE]);
                event_handles[CHILD_HANDLE] = NULL;
            }
        }
