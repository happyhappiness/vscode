ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                        "chunked Transfer-Encoding forbidden: %s", r->uri);