ap_log_rerror(APLOG_MARK, log_flags, rv, r,
                  "%s%s: %s", logno ? logno : "", error, r->filename);