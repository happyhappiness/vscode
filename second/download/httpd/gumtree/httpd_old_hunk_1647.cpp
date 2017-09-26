        runtime->s->lbstatus -= total_factor;
        runtime->s->elected++;

        *worker = runtime;
    }
    else if (route && (*balancer)->sticky_force) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "proxy: BALANCER: (%s). All workers are in error state for route (%s)",
                     (*balancer)->name, route);
        if ((rv = PROXY_THREAD_UNLOCK(*balancer)) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                         "proxy: BALANCER: (%s). Unlock failed for pre_request",
                         (*balancer)->name);
        }
        return HTTP_SERVICE_UNAVAILABLE;
    }

    if ((rv = PROXY_THREAD_UNLOCK(*balancer)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                     "proxy: BALANCER: (%s). Unlock failed for pre_request",
                     (*balancer)->name);
