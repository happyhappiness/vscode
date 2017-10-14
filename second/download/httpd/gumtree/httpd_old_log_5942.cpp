ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(02383)
                "body too big for the cache buffer, not caching: %s",
                h->cache_obj->key);