ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
                          "user '%s' not found: %s", sent_user, r->uri);