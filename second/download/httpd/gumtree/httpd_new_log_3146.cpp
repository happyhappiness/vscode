ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01807)
                          "user '%s': authentication failure for \"%s\": "
                          "password Mismatch",
                          sent_user, r->uri);