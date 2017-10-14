ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                     "proxy: FCGI: Error dispatching request to %s:",
                     server_portstr);