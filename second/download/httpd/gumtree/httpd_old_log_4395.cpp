ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "proxy: FCGI: failed to make connection to backend: %s",
                     backend->hostname);