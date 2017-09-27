
                }
                else {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv,
                            r, APLOGNO(00752) "Cache locked for url, not caching "
                            "response: %s", r->uri);
                }
            }
            else {
                if (cache->stale_headers) {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
                            r, APLOGNO(00753) "Restoring request headers for %s",
