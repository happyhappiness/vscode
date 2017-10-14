ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "Client sent malformed Host header: %s",
                  src);