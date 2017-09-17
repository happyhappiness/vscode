ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                    "client used wrong authentication scheme: %s", r->uri);