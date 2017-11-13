ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, s,
                     "%s: fam %d socket created to connect to %s",
                     proxy_function, backend_addr->family, worker->s->hostname);