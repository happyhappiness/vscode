ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "missing expr in if statement: %s", 
                                  r->filename);