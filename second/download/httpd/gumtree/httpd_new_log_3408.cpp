ap_log_rerror(APLOG_MARK, APLOG_INFO, status, r, APLOGNO(00780)
                "Cache lock file for '%s' too old, removing: %s",
                r->uri, lockname);