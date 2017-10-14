ap_log_error(APLOG_MARK, APLOG_ERR, rv, main_s,
                                 "Failed to resolve server name "
                                 "for %s (check DNS) -- or specify an explicit "
                                 "ServerName",
                                 ipaddr_str);