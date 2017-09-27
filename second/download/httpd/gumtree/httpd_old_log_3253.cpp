ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Query execution error looking up '%s' "
                      "in database", user);