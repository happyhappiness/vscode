ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "DBM user %s: authentication failure for \"%s\": "
                      "Password Mismatch",
                      r->user, r->uri);