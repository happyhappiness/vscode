ap_log_error(APLOG_MARK,APLOG_ERR, apr_get_os_error(), ap_server_conf,
                             "Parent: SetEvent for child process %pp failed",
                             event_handles[CHILD_HANDLE]);