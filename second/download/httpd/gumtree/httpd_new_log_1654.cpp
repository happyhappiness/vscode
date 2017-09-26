ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                     "mem_cache: Discarding body for URL %s "
                     "because client connection was aborted.",
                     obj->key);