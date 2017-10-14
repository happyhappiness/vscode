ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, r->server,
                 "proxy: CONNECT: connecting to remote proxy %s on port %d",
                 connectname, connectport);