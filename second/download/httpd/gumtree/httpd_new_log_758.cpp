ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "Parse error in type map, Content-Length: "
                                  "'%s' in %s is invalid.",
                                  body, r->filename);