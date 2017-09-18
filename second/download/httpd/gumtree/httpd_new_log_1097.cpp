ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: FTP: fam %d socket created, trying to connect to %pI (%s)...", 
                         connect_addr->family, connect_addr, connectname);