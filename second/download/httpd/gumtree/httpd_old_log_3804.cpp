ap_log_error(APLOG_MARK, APLOG_CRIT, rv, main_server,
                     "Couldn't set permissions on unix domain socket %s",
                     sockname);