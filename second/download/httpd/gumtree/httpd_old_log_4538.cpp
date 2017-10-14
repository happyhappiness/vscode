ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "proxy: %s: failed to acquire connection for (%s)",
                     proxy_function, worker->hostname);