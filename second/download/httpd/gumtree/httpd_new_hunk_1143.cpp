     * for balancer, because this is failover attempt.
     */
    if (!*balancer &&
        !(*balancer = ap_proxy_get_balancer(r->pool, conf, *url)))
        return DECLINED;

    /* Step 2: Lock the LoadBalancer
     * XXX: perhaps we need the process lock here
     */
    if ((rv = PROXY_THREAD_LOCK(*balancer)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                     "proxy: BALANCER: (%s). Lock failed for pre_request",
                     (*balancer)->name);
        return DECLINED;
    }

    /* Step 3: force recovery */
    force_recovery(*balancer, r->server);

    /* Step 4: find the session route */
    runtime = find_session_route(*balancer, r, &route, &sticky, url);
    if (runtime) {
        int i, total_factor = 0;
        proxy_worker *workers;
        /* We have a sticky load balancer
         * Update the workers status
         * so that even session routes get
