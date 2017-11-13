ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                         "SSL client authentication failed: %s",
                         error ? error : "unknown");