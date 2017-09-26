ap_log_error(APLOG_MARK, APLOG_EMERG, status, ap_server_conf,
                     "Couldn't create pollset in child; check system or user limits");