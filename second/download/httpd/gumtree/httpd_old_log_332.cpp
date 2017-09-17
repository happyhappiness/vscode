ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                             "attempt to make remote request from mod_rewrite "
                             "without proxy enabled: %s", r->filename);