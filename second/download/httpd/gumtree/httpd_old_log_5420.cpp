ap_log_error(APLOG_MARK, APLOG_NOTICE,
                             0, ap_server_conf,
                             "child pid %ld exit signal %s (%d)",
                             (long)pid->pid, sigdesc, signum);