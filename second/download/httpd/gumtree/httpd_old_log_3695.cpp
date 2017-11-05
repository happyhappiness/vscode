ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: Creating roundrobin ctx for BALANCER %s (%d)",
                 balancer->name, (int)getpid());