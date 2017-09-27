                member_of = 1;
                break;
            }
            workers++;
        }
        if (member_of) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01167)
                          "%s: All workers are in error state for route (%s)",
                          (*balancer)->s->name, route);
            if ((rv = PROXY_THREAD_UNLOCK(*balancer)) != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01168)
                              "%s: Unlock failed for pre_request",
                              (*balancer)->s->name);
            }
            return HTTP_SERVICE_UNAVAILABLE;
        }
    }

    if ((rv = PROXY_THREAD_UNLOCK(*balancer)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01169)
                      "%s: Unlock failed for pre_request",
                      (*balancer)->s->name);
    }
    if (!*worker) {
        runtime = find_best_worker(*balancer, r);
        if (!runtime) {
            if ((*balancer)->workers->nelts) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01170)
                              "%s: All workers are in error state",
                              (*balancer)->s->name);
            } else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01171)
                              "%s: No workers in balancer",
                              (*balancer)->s->name);
            }

            return HTTP_SERVICE_UNAVAILABLE;
        }
        if (*(*balancer)->s->sticky && runtime) {
            /*
             * This balancer has sticky sessions and the client either has not
             * supplied any routing information or all workers for this route
             * including possible redirect and hotstandby workers are in error
             * state, but we have found another working worker for this
             * balancer where we can send the request. Thus notice that we have
