ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                      "%s with body is not allowed for %s", r->method, r->uri);