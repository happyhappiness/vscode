ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                                  "missing expr in elif statement: %s", 
                                  r->filename);