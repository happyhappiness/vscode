            exitcode = APEXIT_CHILDFATAL;
        }
        if (   exitcode == APEXIT_CHILDFATAL
            || exitcode == APEXIT_CHILDINIT
            || exitcode == APEXIT_INIT) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, 0, ap_server_conf, APLOGNO(00427)
                         "Parent: child process exited with status %lu -- Aborting.", exitcode);
            shutdown_pending = 1;
        }
        else {
            int i;
            restart_pending = 1;
            ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf, APLOGNO(00428)
                         "Parent: child process exited with status %lu -- Restarting.", exitcode);
            for (i = 0; i < ap_threads_per_child; i++) {
                ap_update_child_status_from_indexes(0, i, SERVER_DEAD, NULL);
            }
        }
        CloseHandle(event_handles[CHILD_HANDLE]);
        event_handles[CHILD_HANDLE] = NULL;
