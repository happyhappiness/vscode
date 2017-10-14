ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01645)
                      "authz_dbd: query for %s failed; user %s [%s]",
                      action, r->user, message?message:noerror);