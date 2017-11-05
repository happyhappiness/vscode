ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
        "proxy: BALANCER: (%s). Unlock failed for find_best_worker()", balancer->name);