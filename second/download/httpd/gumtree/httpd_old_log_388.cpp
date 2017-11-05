ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf, 
                     "Child %d: Terminating %d threads that failed to exit.", my_pid);