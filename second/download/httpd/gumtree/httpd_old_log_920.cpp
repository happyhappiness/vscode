ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, ap_server_conf, 
                         "Parent: child process exited with status %u -- Aborting.", exitcode);