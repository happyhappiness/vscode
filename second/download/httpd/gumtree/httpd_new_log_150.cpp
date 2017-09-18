ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, 
                     r->server,
                     "cache: Last modified is in the future, "
                     "replacing with now");