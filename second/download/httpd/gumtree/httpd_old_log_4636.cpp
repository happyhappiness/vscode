ap_log_rerror(APLOG_MARK, loglevel, rv, r,
                          "proxy: %s: error creating fam %d socket for target %s",
                          proxy_function,
                          backend_addr->family,
                          backend_name);