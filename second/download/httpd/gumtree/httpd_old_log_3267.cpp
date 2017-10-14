ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "authz_dbd in get_row; action=%s user=%s [%s]",
                          action, r->user, message?message:noerror);