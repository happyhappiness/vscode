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
