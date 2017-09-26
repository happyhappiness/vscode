    return NULL;
}

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
    *route = get_path_param(r->pool, *url, sticky_path);
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
