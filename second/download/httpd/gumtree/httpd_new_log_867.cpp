ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "proxy: %s: connection complete to %pI (%s)",
                 proxy_function, backend_addr, conn->hostname);