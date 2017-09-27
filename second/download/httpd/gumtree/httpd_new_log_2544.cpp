ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                              "access to %s denied", r->uri);