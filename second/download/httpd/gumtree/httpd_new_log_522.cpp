ap_log_error(APLOG_MARK, log_level, rv, ap_server_conf,
                     "connect to listener on %pI", ap_listeners->bind_addr);