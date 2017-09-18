ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf, 
                         "Parent: child process exited with status %u -- Restarting.", exitcode);