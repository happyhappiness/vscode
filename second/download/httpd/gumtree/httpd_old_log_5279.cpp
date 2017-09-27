ap_log_error(APLOG_MARK, APLOG_EMERG, status, ap_server_conf,
                         "Couldn't add listener to pollset; check system or user limits");