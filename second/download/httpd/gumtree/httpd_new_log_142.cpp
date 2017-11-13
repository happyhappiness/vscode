ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Forbidden: %s doesn't point to "
                              "a file or directory",
                              r->filename);