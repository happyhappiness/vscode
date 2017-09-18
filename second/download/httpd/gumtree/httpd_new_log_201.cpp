ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                           "variable must precede value in set directive in %s",
                           r->filename);