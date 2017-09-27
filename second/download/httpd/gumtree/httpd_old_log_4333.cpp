ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                     "proxy: BALANCER: (%s). Lock failed for pre_request",
                     (*balancer)->name);