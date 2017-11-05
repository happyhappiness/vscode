ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00783)
                "Cache already locked for stale cached URL, "
                "pretend it is fresh: %s",
                r->unparsed_uri);