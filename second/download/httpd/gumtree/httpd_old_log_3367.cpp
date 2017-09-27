ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "authz_dbd, in groups query for %s [%s]",
                      r->user, message?message:noerror);