ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                     "Child %lu: Unable to access the start_mutex from the parent", my_pid);