ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                         c->base_server,
                         "SSL client authentication failed: %s",
                         error ? error : "unknown");