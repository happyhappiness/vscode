ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Syntax error in type map, no ':' in %s for header %s",
                      r->filename, header);