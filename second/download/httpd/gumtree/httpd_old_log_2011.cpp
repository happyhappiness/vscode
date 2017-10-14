ap_log_error(APLOG_MARK, loglevel, rv, s,
                         "proxy: %s: attempt to connect to %pI (%s) failed",
                         proxy_function,
                         backend_addr,
                         backend_name);