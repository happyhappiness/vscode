                member_of = 1;
                break;
            }
            workers++;
        }
        if (member_of) {
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
    }

    if ((rv = PROXY_THREAD_UNLOCK(*balancer)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                     "proxy: BALANCER: (%s). Unlock failed for pre_request",
                     (*balancer)->name);
    }
    if (!*worker) {
        runtime = find_best_worker(*balancer, r);
        if (!runtime) {
            if ((*balancer)->workers->nelts) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                            "proxy: BALANCER: (%s). All workers are in error state",
                            (*balancer)->name);
            } else {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                            "proxy: BALANCER: (%s). No workers in balancer",
                            (*balancer)->name);
            }

            return HTTP_SERVICE_UNAVAILABLE;
        }
        if ((*balancer)->sticky && runtime) {
            /*
             * This balancer has sticky sessions and the client either has not
             * supplied any routing information or all workers for this route
             * including possible redirect and hotstandby workers are in error
             * state, but we have found another working worker for this
             * balancer where we can send the request. Thus notice that we have
