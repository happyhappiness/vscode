ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                         "Child %lu: Process exiting because it reached "
                         "MaxRequestsPerChild. Signaling the parent to "
                         "restart a new child process.", my_pid);