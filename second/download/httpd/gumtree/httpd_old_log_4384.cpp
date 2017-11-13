ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "proxy: FCGI: Got bogus version %d",
                             (int) header.version);