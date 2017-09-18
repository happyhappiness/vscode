            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                         "Parent: Unable to write duplicated socket %d to the child.", lr->sd );
            return -1;
        }
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                 "Parent: Sent %d listeners to child %d", lcnt, dwProcessId);
    return 0;
}

static int create_process(apr_pool_t *p, HANDLE *child_proc, HANDLE *child_exit_event, 
                          DWORD *child_pid)
