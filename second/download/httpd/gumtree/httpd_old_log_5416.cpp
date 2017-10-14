ap_log_error(APLOG_MARK, APLOG_NOTICE, rv, ap_server_conf,
                     "cannot send signal %d to pid %ld (non-child or "
                     "already dead)", sig, (long)pid);