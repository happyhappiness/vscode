ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "form parsed, but password field '%s' was missing or empty, unauthorized",
                      password);