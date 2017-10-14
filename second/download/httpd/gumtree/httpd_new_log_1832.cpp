ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                     "cgi: apr_pollset_create(); check system or user limits");