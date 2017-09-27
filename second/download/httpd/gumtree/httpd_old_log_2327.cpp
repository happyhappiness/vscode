ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf,
                     "Child %lu: Failure releasing the start mutex", my_pid);