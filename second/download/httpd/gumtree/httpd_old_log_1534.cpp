ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                             "proxy: BALANCER: (%s).  Forcing recovery for worker (%s), failonstatus %d",
                             balancer->name, worker->name, val);