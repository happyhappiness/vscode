ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                (direct_connect) ? APLOGNO(03231) "NoProxy for %s" : APLOGNO(03232) "UseProxy for %s",
                r->uri);