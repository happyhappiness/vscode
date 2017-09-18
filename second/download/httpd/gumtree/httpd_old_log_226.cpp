ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                          "chunked Transfer-Encoding forbidden: %s", r->uri);