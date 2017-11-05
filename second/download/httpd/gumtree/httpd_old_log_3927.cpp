ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                                 "proxy: FTP: PASV attempt to connect to %pI failed - Firewall/NAT?", pasv_addr);