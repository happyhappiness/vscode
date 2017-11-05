ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                             "cache: error returned while trying to return %s "
                             "cached data", 
                             cache->type);