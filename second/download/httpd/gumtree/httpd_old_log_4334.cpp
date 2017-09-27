ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                         "proxy: BALANCER: (%s). All workers are in error state for route (%s)",
                         (*balancer)->name, route);