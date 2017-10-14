ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01652)
                      "authz_dbd, in groups query for %s [%s]",
                      r->user, message?message:noerror);