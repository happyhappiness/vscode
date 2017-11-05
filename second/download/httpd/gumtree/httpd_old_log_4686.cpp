ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                                     "Child %d: Encountered too many AcceptEx "
                                     "faults accepting client connections.",
                                     my_pid);