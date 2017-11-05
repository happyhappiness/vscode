ap_log_error(APLOG_MARK, APLOG_INFO, status, r->server,
                             "proxy: HTTP: 100-Continue failed to %pI (%s)",
                             worker->cp->addr, worker->hostname);