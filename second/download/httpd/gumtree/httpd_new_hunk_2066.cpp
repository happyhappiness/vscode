     * This replaces the balancers fictional name with the
     * real hostname of the elected worker.
     */
    access_status = rewrite_url(r, *worker, url);
    /* Add the session route to request notes if present */
    if (route) {
        apr_table_setn(r->notes, "session-sticky", sticky);
        apr_table_setn(r->notes, "session-route", route);

        /* Add session info to env. */
        apr_table_setn(r->subprocess_env,
                       "BALANCER_SESSION_STICKY", sticky);
        apr_table_setn(r->subprocess_env,
                       "BALANCER_SESSION_ROUTE", route);
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: BALANCER (%s) worker (%s) rewritten to %s",
                 (*balancer)->name, (*worker)->name, *url);
