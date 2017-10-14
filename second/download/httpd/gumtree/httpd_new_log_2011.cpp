ap_log_rerror(APLOG_MARK, loglevel, rv, r,
                          "proxy: %s: attempt to connect to %pI (%s) failed",
                          proxy_function,
                          backend_addr,
                          backend_name);