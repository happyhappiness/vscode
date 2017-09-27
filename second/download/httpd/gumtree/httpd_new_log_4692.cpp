ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                         s, APLOGNO(00961) "%s: failed to enable ssl support "
                         "for %pI (%s)", proxy_function,
                         backend_addr, conn->hostname);