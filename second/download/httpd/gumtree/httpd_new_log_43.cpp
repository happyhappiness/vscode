ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Digest: internal error: couldn't find session "
                              "info for user %s", resp->username);