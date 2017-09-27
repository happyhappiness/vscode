r(APLOG_MARK, APLOG_TRACE2, 0, s,
                     "proxy: %s: fam %d socket created to connect to %s",
                     proxy_function, backend_addr->family, worker->hostname);