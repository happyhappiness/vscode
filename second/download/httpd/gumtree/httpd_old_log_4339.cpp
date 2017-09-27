r(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: BALANCER (%s) worker (%s) rewritten to %s",
                 (*balancer)->name, (*worker)->name, *url);