ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
                          "user '%s': authentication failure for \"%s\": "
                          "password Mismatch",
                          sent_user, r->uri);