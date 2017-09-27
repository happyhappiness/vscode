    /* Step 1: check if the url is for us
     * The url we can handle starts with 'balancer://'
     * If balancer is already provided skip the search
     * for balancer, because this is failover attempt.
     */
    if (!*balancer &&
        !(*balancer = ap_proxy_get_balancer(r->pool, conf, *url, 1)))
        return DECLINED;

    /* Step 2: Lock the LoadBalancer
     * XXX: perhaps we need the process lock here
     */
    if ((rv = PROXY_THREAD_LOCK(*balancer)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01166)
                      "%s: Lock failed for pre_request", (*balancer)->s->name);
        return DECLINED;
    }

    /* Step 3: force recovery */
    force_recovery(*balancer, r->server);

    /* Step 3.5: Update member list for the balancer */
    /* TODO: Implement as provider! */
    ap_proxy_sync_balancer(*balancer, r->server, conf);

    /* Step 4: find the session route */
    runtime = find_session_route(*balancer, r, &route, &sticky, url);
    if (runtime) {
        if ((*balancer)->lbmethod && (*balancer)->lbmethod->updatelbstatus) {
            /* Call the LB implementation */
