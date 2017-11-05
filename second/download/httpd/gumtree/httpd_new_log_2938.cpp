ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(00784)
                "Attempt to obtain a cache lock for stale "
                "cached URL failed, revalidating entry anyway: %s",
                r->unparsed_uri);