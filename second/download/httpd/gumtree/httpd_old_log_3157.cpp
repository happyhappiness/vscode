ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                     "buggy client used un-escaped hash in Request-URI");