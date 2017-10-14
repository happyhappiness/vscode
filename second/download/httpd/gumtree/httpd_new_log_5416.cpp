ap_log_error(APLOG_MARK, APLOG_NOTICE, rv, ap_server_conf, APLOGNO(00048)
                     "cannot send signal %d to pid %ld (non-child or "
                     "already dead)", sig, (long)pid);