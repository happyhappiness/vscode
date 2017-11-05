ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                             ap_server_conf,
                             "removed PID file %s (pid=%" APR_PID_T_FMT ")",
                             pidfile, getpid());