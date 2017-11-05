ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                      "proxy: an error occurred creating a new connection "
                      "to %pI (%s)", connect_addr, connectname);