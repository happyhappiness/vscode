ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, ap_server_conf,
                         "select/accept error (%d)", status);