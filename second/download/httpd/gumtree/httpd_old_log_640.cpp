ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "unknown parameter \"%s\" to tag config in %s",
                              tag, r->filename);