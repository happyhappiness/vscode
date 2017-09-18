ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "cache_mem: URL %s failed the size check, "
                         "or is incomplete", 
                         key);