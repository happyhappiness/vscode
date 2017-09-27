                                                 &proxy_module);

    apr_pool_t *p = r->pool;

    apr_uri_t *uri = apr_palloc(r->pool, sizeof(*uri));

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: FCGI: url: %s proxyname: %s proxyport: %d",
                 url, proxyname, proxyport);

    if (strncasecmp(url, "fcgi:", 5) == 0) {
        url += 5;
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: FCGI: declining URL %s", url);
        return DECLINED;
    }
    
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: FCGI: serving URL %s", url);

    /* Create space for state information */
    if (! backend) {
        status = ap_proxy_acquire_connection(FCGI_SCHEME, &backend, worker,
                                             r->server);
        if (status != OK) {
