ap_log_rerror(APLOG_MARK, APLOG_ERR,
                      0, r, LOG_PREFIX "need AuthName: %s", r->uri);