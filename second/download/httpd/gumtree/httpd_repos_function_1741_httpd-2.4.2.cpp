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
    else if (route && (*balancer)->s->sticky_force) {
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
             * changed the route to the backend.
             */
            apr_table_setn(r->subprocess_env, "BALANCER_ROUTE_CHANGED", "1");
        }
        *worker = runtime;
    }

    (*worker)->s->busy++;

    /* Add balancer/worker info to env. */
    apr_table_setn(r->subprocess_env,
                   "BALANCER_NAME", (*balancer)->s->name);
    apr_table_setn(r->subprocess_env,
                   "BALANCER_WORKER_NAME", (*worker)->s->name);
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
        apr_table_setn(r->notes, "session-sticky", sticky);
        apr_table_setn(r->notes, "session-route", route);

        /* Add session info to env. */
        apr_table_setn(r->subprocess_env,
                       "BALANCER_SESSION_STICKY", sticky);
        apr_table_setn(r->subprocess_env,
                       "BALANCER_SESSION_ROUTE", route);
    }
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01172)
                  "%s: worker (%s) rewritten to %s",
                  (*balancer)->s->name, (*worker)->s->name, *url);

    return access_status;
}