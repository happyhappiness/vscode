ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                              "access to %s failed (filesystem path '%s')", 
                              r->uri, r->filename);