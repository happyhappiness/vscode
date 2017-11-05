ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: FTP: an error occurred creating a new connection to %pI (%s)",
                     connect_addr, connectname);