ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "access to %s failed, reason: unable to get the "
                      "remote host name", r->uri);