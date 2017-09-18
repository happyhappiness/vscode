ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                             "attempt to make remote request from mod_rewrite "
                             "without proxy enabled: %s", r->filename);