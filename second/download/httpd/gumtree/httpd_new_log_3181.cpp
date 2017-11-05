ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                                  "Not compressing (content-encoding already "
                                  " set: %s)", token);