ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: CONNECT: woke from select(), i=%d", pollcnt);