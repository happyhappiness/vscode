        *worker = runtime;
    }
    else if (route && (*balancer)->sticky_force) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "proxy: BALANCER: (%s). All workers are in error state for route (%s)",
                     (*balancer)->name, route);
        PROXY_THREAD_UNLOCK(*balancer);
        return HTTP_SERVICE_UNAVAILABLE;
    }

    PROXY_THREAD_UNLOCK(*balancer);
    if (!*worker) {
        runtime = find_best_worker(*balancer, r);
        if (!runtime) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                         "proxy: BALANCER: (%s). All workers are in error state",
                         (*balancer)->name);

            return HTTP_SERVICE_UNAVAILABLE;
        }
        *worker = runtime;
    }

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
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: BALANCER (%s) worker (%s) rewritten to %s",
                 (*balancer)->name, (*worker)->name, *url);

    return access_status;
