ap_log_error(APLOG_MARK, APLOG_ALERT,
                         0, ap_server_conf,
                         "Child %" APR_PID_T_FMT
                         " returned a Fatal error... Apache is exiting!",
                         pid->pid);