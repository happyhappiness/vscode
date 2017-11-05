ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                     "proxy: FCGI: Failed Writing Request to %s:",
                     server_portstr);