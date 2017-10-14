ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: Entering roundrobin for BALANCER %s (%d)",
                 balancer->name, (int)getpid());