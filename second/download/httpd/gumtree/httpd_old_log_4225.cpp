ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "proxy: BALANCER: (%s). Forcing recovery for worker (%s)",
                         balancer->name, (*worker)->hostname);