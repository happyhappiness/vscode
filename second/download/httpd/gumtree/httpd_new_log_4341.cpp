ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01174)
                              "%s:  Forcing recovery for worker (%s), "
                              "failonstatus %d",
                              balancer->s->name, worker->s->name, val);