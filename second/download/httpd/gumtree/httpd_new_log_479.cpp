ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, 
                          "access to %s failed, reason: %s",
                          r->filename, cp);