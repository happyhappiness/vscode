ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "authz_dbd: query for %s failed; user %s [%s]",
                      action, r->user, message?message:noerror);