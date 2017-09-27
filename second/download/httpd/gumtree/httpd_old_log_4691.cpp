ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                     s, "proxy: %s: an error occurred creating a "
                     "new connection to %pI (%s)", proxy_function,
                     backend_addr, conn->hostname);