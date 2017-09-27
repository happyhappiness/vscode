ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                     "cgi: apr_pollset_add(); check system or user limits");