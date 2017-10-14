ap_log_error(APLOG_MARK, APLOG_ERR,
                     0, ap_server_conf,
                     "could not make child process %" APR_PID_T_FMT
                     " exit, "
                     "attempting to continue anyway",
                     pid);