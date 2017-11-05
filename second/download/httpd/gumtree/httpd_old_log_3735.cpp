ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: BALANCER: Route changed from %s to %s",
                         *route, worker->s->route);