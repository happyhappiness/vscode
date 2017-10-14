ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                         "socache: Failed to Create memcache Server: %s:%d", 
                         host_str, port);