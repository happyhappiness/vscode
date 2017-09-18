ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r->server,
                         "proxy: FTP: trying to connect to %pI (%s)...", connect_addr, connectname);