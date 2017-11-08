static proxy_worker *find_session_route(proxy_balancer *balancer,
                                        request_rec *r,
                                        char **route,
                                        char **sticky_used,
                                        char **url)
{
    proxy_worker *worker = NULL;
    char *sticky, *sticky_path, *path;

    if (!balancer->sticky)
        return NULL;
    sticky = sticky_path = apr_pstrdup(r->pool, balancer->sticky);
    if ((path = strchr(sticky, '|'))) {
        *path++ = '\0';
         sticky_path = path;
    }
    
    /* Try to find the sticky route inside url */
    *sticky_used = sticky_path;
    *route = get_path_param(r->pool, *url, sticky_path, balancer->scolonsep);
    if (!*route) {
        *route = get_cookie_param(r, sticky);
        *sticky_used = sticky;
    }
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