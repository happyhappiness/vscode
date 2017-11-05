ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                     "Couldn't create pollset in thread;"
                     " check system or user limits");