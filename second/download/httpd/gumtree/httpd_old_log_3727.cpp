ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                         "proxy: AJP: failed to make connection to backend: %s",
                         backend->hostname);