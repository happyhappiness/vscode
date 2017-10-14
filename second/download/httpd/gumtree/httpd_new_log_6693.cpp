ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r, APLOGNO(03461)
                  "attempting to match URI path '%s' against %s '%s' for "
                  "proxying", r->uri, (ent->regex ? "pattern" : "prefix"),
                  fake);