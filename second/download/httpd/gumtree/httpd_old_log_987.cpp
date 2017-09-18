ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR,
                      0, r, "need AuthType to note auth failure: %s", r->uri);