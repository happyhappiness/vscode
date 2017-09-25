ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "cache_disk: Error when writing cache file for URL %s",
                     h->cache_obj->key);