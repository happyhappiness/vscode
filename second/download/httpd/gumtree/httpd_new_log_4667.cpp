ap_log_rerror(APLOG_MARK, loglevel, rv, r, APLOGNO(00935)
                          "%s: error creating fam %d socket for target %s",
                          proxy_function, backend_addr->family, backend_name);