                                        char **route,
                                        const char **sticky_used,
                                        char **url)
{
    proxy_worker *worker = NULL;

    if (!balancer->sticky)
        return NULL;
    /* Try to find the sticky route inside url */
    *route = get_path_param(r->pool, *url, balancer->sticky_path, balancer->scolonsep);
    if (*route) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: BALANCER: Found value %s for "
                     "stickysession %s", *route, balancer->sticky_path);
        *sticky_used =  balancer->sticky_path;
    }
    else {
        *route = get_cookie_param(r, balancer->sticky);
        if (*route) {
            *sticky_used =  balancer->sticky;
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: BALANCER: Found value %s for "
                         "stickysession %s", *route, balancer->sticky);
        }
    }
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
        worker = find_route_worker(balancer, *route, r);
        if (worker && strcmp(*route, worker->s->route)) {
            /*
             * Notice that the route of the worker chosen is different from
             * the route supplied by the client.
             */
            apr_table_setn(r->subprocess_env, "BALANCER_ROUTE_CHANGED", "1");
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: BALANCER: Route changed from %s to %s",
                         *route, worker->s->route);
        }
        return worker;
    }
    else
        return NULL;
}
