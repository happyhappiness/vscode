ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00768)
                "cache: %s not cached for request %s. Reason: %s",
                cache->key, r->unparsed_uri, reason);