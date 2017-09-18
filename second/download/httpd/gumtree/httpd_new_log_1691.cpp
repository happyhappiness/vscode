ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                         "disk_cache: Discarding body for URL %s "
                         "because connection has been aborted.",
                         h->cache_obj->key);