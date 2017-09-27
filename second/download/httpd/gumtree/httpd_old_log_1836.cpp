ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "Encountered premature end-of-stream while "
                                  "reading inflate header");