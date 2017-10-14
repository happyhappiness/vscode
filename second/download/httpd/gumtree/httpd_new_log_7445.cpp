ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01174)
                              "%s: Forcing worker (%s) into error state "
                              "due to status code %d matching 'failonstatus' "
                              "balancer parameter",
                              balancer->s->name, ap_proxy_worker_name(r->pool, worker),
                              val);