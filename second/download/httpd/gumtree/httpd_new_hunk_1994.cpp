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
    }
    if (!*worker) {
        runtime = find_best_worker(*balancer, r);
        if (!runtime) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                         "proxy: BALANCER: (%s). All workers are in error state",
                         (*balancer)->name);

            return HTTP_SERVICE_UNAVAILABLE;
        }
        if ((*balancer)->sticky && runtime) {
            /*
             * This balancer has sticky sessions and the client either has not
             * supplied any routing information or all workers for this route
             * including possible redirect and hotstandby workers are in error
             * state, but we have found another working worker for this
             * balancer where we can send the request. Thus notice that we have
             * changed the route to the backend.
             */
            apr_table_setn(r->subprocess_env, "BALANCER_ROUTE_CHANGED", "1");
        }
        *worker = runtime;
    }

    /* Add balancer/worker info to env. */
    apr_table_setn(r->subprocess_env,
                   "BALANCER_NAME", (*balancer)->name);
    apr_table_setn(r->subprocess_env,
                   "BALANCER_WORKER_NAME", (*worker)->name);
    apr_table_setn(r->subprocess_env,
                   "BALANCER_WORKER_ROUTE", (*worker)->s->route);

    /* Rewrite the url from 'balancer://url'
     * to the 'worker_scheme://worker_hostname[:worker_port]/url'
     * This replaces the balancers fictional name with the
     * real hostname of the elected worker.
     */
    access_status = rewrite_url(r, *worker, url);
    /* Add the session route to request notes if present */
    if (route) {
        apr_table_setn(r->notes, "session-sticky", (*balancer)->sticky);
        apr_table_setn(r->notes, "session-route", route);

        /* Add session info to env. */
        apr_table_setn(r->subprocess_env,
                       "BALANCER_SESSION_STICKY", (*balancer)->sticky);
        apr_table_setn(r->subprocess_env,
                       "BALANCER_SESSION_ROUTE", route);
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: BALANCER (%s) worker (%s) rewritten to %s",
                 (*balancer)->name, (*worker)->name, *url);

    return access_status;
