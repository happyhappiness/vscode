ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                     "proxy: FCGI: Failed writing Environment to %s:",
                     server_portstr);