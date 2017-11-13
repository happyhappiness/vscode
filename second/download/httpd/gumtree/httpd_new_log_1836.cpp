ap_log_error(APLOG_MARK, APLOG_ERR, rv,
                             main_server,
                             "Error writing pid %" APR_PID_T_FMT " to handler", pid);