ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01167)
                          "%s: All workers are in error state for route (%s)",
                          (*balancer)->s->name, route);