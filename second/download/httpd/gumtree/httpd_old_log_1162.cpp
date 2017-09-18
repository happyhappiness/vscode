ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf, 
                 "Child %d: Starting %d worker threads.", my_pid, ap_threads_per_child);