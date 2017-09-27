            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01160)
                         "Found value %s for stickysession %s",
                         *route, balancer->s->sticky);
        }
    }
    /*
     * If we found a value for sticksession, find the first '.' within.
     * Everything after '.' (if present) is our route.
     */
    if ((*route) && ((*route = strchr(*route, '.')) != NULL ))
        (*route)++;
    if ((*route) && (**route)) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01161) "Found route %s", *route);
        /* We have a route in path or in cookie
         * Find the worker that has this route defined.
         */
