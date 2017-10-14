ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, APLOGNO(01117)
                 "proxy: Creating roundrobin ctx for BALANCER %s (%d)",
                 balancer->name, (int)getpid());