ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01651)
                        "authz_dbd in get_row; group query for user=%s [%s]",
                        r->user, message?message:noerror);