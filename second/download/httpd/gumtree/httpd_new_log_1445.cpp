ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                         "[strict] purely numeric host names not allowed: %s",
                         src);