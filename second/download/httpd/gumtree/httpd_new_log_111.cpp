ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_CRIT, r,
                    "configuration error:  couldn't %s: %s", phase, r->uri);