    return NULL;
}

static proxy_worker *find_session_route(proxy_balancer *balancer,
                                        request_rec *r,
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
