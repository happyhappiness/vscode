ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                             "proxy: BALANCER: (%s).  Forcing worker (%s) into error state "
                             "due to status code %d matching 'failonstatus' "
                             "balancer parameter",
                             balancer->name, worker->name, val);