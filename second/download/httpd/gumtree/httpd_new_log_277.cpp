ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "missing closing endif directive in parsed document"
                          " %s", r->filename);