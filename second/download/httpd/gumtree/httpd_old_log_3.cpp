ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                      "user %s: authentication failure for \"%s\": "
                      "Password Mismatch",
                      r->user, r->uri);