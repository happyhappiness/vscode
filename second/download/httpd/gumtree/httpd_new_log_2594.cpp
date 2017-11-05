ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                         "proxy: HTTP: failed to make connection to backend: %s",
                         backend->hostname);