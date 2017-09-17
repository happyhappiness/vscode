ap_log_rerror(APLOG_MARK, APLOG_ALERT|APLOG_NOERRNO, r, "%s: %s",
                        filename, errmsg);