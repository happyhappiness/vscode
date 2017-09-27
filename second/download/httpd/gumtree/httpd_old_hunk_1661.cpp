        url += 9;
    }
    else {
        return DECLINED;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
             "proxy: BALANCER: canonicalising URL %s", url);

    /* do syntatic check.
     * We break the URL into host, port, path, search
     */
    err = ap_proxy_canon_netloc(r->pool, &url, NULL, NULL, &host, &port);
