ap_log_error(APLOG_MARK, APLOG_INFO, APR_SUCCESS, ap_server_conf,
                     "Parent: Duplicating socket %d and sending it to child process %d",
                     nsd, dwProcessId);