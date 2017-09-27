ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                            "proxy: BALANCER: Found value %s for "
                            "stickysession %s", *route, balancer->sticky);