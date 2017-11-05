ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                (direct_connect) ? "NoProxy for %s" : "UseProxy for %s",
                r->uri);