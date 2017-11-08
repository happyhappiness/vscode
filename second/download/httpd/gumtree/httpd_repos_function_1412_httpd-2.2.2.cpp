static proxy_worker *find_session_route(proxy_balancer *balancer,
                                        request_rec *r,
                                        char **route,
                                        char **url)
{
    proxy_worker *worker = NULL;

    if (!balancer->sticky)
        return NULL;
    /* Try to find the sticky route inside url */
    *route = get_path_param(r->pool, *url, balancer->sticky);
    if (!*route)
        *route = get_cookie_param(r, balancer->sticky);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                            "proxy: BALANCER: Found value %s for "
                            "stickysession %s", *route, balancer->sticky);
    /*
     * If we found a value for sticksession, find the first '.' within.
     * Everything after '.' (if present) is our route.
     */
    if ((*route) && ((*route = strchr(*route, '.')) != NULL ))
        (*route)++;
    if ((*route) && (**route)) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                                  "proxy: BALANCER: Found route %s", *route);
        /* We have a route in path or in cookie
         * Find the worker that has this route defined.
         */
        worker = find_route_worker(balancer, *route);
        if (worker && !PROXY_WORKER_IS_USABLE(worker)) {
            /* We have a worker that is unusable.
             * It can be in error or disabled, but in case
             * it has a redirection set use that redirection worker.
             * This enables to safely remove the member from the
             * balancer. Of course you will need a some kind of
             * session replication between those two remote.
             */
            if (*worker->s->redirect)
                worker = find_route_worker(balancer, worker->s->redirect);
            /* Check if the redirect worker is usable */
            if (worker && !PROXY_WORKER_IS_USABLE(worker))
                worker = NULL;
        }
        return worker;
    }
    else
        return NULL;
}