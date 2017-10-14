ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf,
                                 "Child %d: Encountered too many errors accepting client connections. "
                                 "Possible causes: Unknown. "
                                 "Try using the Win32DisableAcceptEx directive.", my_pid);