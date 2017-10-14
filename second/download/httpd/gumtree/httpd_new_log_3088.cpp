ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "Buggy authn provider failed to set user for %s",
                                  r->uri);