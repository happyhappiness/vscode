ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01617)
                      "user %s: authentication failure for \"%s\": "
                      "Password Mismatch",
                      sent_user, r->uri);