ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                            "proxy: BALANCER: (%s). No workers in balancer",
                            (*balancer)->name);