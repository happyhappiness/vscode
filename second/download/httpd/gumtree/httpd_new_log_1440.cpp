ap_log_error(APLOG_MARK,APLOG_INFO, APR_SUCCESS, ap_server_conf,
                         "Child %lu: %d threads blocked on the completion port", my_pid, g_blocked_threads);