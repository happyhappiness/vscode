ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                    "client sent illegal HTTP/0.9 request: %s", r->uri);