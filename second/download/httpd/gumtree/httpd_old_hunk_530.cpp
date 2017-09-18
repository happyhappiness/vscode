            /* HUH? We did exit, didn't we? */
            exitcode = APEXIT_CHILDFATAL;
        }
        if (   exitcode == APEXIT_CHILDFATAL 
            || exitcode == APEXIT_CHILDINIT
            || exitcode == APEXIT_INIT) {
            ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, ap_server_conf, 
                         "Parent: child process exited with status %u -- Aborting.", exitcode);
        }
        else {
            restart_pending = 1;
            ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_NOTICE, APR_SUCCESS, ap_server_conf, 
                         "Parent: child process exited with status %u -- Restarting.", exitcode);
        }
        CloseHandle(event_handles[CHILD_HANDLE]);
        event_handles[CHILD_HANDLE] = NULL;
    }
    if (restart_pending) {
        ++ap_my_generation;
