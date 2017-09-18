ap_log_rerror(APLOG_MARK, APLOG_ALERT|APLOG_NOERRNO, 0, r,
                              "%s: %s", filename, errmsg);