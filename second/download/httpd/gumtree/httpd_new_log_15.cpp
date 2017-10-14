ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                                 "mem_cache: URL %s didn't receive complete response, not caching",
                                 h->cache_obj->key);