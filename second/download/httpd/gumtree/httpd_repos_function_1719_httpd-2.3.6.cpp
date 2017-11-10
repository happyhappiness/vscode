static int proxy_balancer_pre_request(proxy_worker **worker,
                                      proxy_balancer **balancer,
                                      request_rec *r,
                                      proxy_server_conf *conf, char **url)
{
    int access_status;
    proxy_worker *runtime;
    char *route = NULL;
    const char *sticky = NULL;
    apr_status_t rv;

    *worker = NULL;
    /* Step 1: check if the url is for us
     * The url we can handle starts with 'balancer://'
     * If balancer is already provided skip the search
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
        if ((*balancer)->lbmethod && (*balancer)->lbmethod->updatelbstatus) {
            /* Call the LB implementation */
            (*balancer)->lbmethod->updatelbstatus(*balancer, runtime, r->server);
        }
        else { /* Use the default one */
            int i, total_factor = 0;
            proxy_worker **workers;
            /* We have a sticky load balancer
             * Update the workers status
             * so that even session routes get
             * into account.
             */
            workers = (proxy_worker **)(*balancer)->workers->elts;
            for (i = 0; i < (*balancer)->workers->nelts; i++) {
                /* Take into calculation only the workers that are
                 * not in error state or not disabled.
                 */
                if (PROXY_WORKER_IS_USABLE(*workers)) {
                    (*workers)->s->lbstatus += (*workers)->s->lbfactor;
                    total_factor += (*workers)->s->lbfactor;
                }
                workers++;
            }
            runtime->s->lbstatus -= total_factor;
        }
        runtime->s->elected++;

        *worker = runtime;
    }
    else if (route && (*balancer)->sticky_force) {
        int i, member_of = 0;
        proxy_worker **workers;
        /*
         * We have a route provided that doesn't match the
         * balancer name. See if the provider route is the
         * member of the same balancer in which case return 503
         */
        workers = (proxy_worker **)(*balancer)->workers->elts;
        for (i = 0; i < (*balancer)->workers->nelts; i++) {
            if (*((*workers)->s->route) && strcmp((*workers)->s->route, route) == 0) {
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
                ap_log_error(APLOG_M