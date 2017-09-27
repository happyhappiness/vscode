ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                         "Couldn't create add listener to pollset;"
                         " check system or user limits");