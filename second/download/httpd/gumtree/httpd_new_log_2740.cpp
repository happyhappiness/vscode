ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, 
                             ap_server_conf,
                             "Child %d: Waiting %d more seconds "
                             "for %d worker threads to finish.", 
                             my_pid, time_remains / 1000, threads_created);