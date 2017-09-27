ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01647)
                          "authz_dbd in get_row; action=%s user=%s [%s]",
                          action, r->user, message?message:noerror);