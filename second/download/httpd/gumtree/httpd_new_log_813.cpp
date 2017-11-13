ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                         "proxy: %s: disabled connection for (%s)",
                         proxy_function, worker->hostname);