ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv,
                        r, APLOGNO(00760) "Cache locked for url, not caching "
                        "response: %s", r->uri);