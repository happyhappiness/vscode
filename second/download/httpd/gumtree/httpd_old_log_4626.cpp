ap_log_error(APLOG_MARK, APLOG_WARNING, 0, r->server,
                                 "proxy: connect to remote machine %s blocked: IP %s matched", uri_addr->hostname, conf_ip);