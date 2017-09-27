ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                     "Child %d: Unable to access the scoreboard from the parent", my_pid);