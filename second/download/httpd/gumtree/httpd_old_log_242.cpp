ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                                  "Syntax error in type map, no end tag '%s'"
                                  "found in %s for Body: content.", 
                                  tag, r->filename);