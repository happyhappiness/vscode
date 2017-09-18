ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_NOTICE,
                         0, ap_server_conf,
                         "seg fault or similar nasty error detected "
                         "in the parent process");