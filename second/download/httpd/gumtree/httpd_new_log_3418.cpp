ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv,
                            r, APLOGNO(00752) "Cache locked for url, not caching "
                            "response: %s", r->uri);