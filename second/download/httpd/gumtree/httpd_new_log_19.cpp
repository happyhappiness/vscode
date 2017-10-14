ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                             r->server, "proxy: bad HTTP/%d.%d status line "
                             "returned by %s (%s)", major, minor, r->uri,
                             r->method);