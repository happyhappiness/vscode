ap_log_error(APLOG_MARK, APLOG_ERR,
                             0, ap_server_conf,
                             "could not make child process %ld exit, "
                             "attempting to continue anyway",
                             (long)pid);