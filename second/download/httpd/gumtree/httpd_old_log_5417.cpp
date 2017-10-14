ap_log_error(APLOG_MARK, APLOG_ALERT, 0, ap_server_conf,
                     "refusing to send signal %d to pid %ld outside "
                     "process group", sig, (long)pid);