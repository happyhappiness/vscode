ap_log_error(APLOG_MARK, APLOG_CRIT, 0, NULL,
                     "Server MUST relinquish startup privileges before "
                     "accepting connections.  Please ensure mod_unixd "
                     "or other system security module is loaded.");