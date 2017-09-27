    if (strncasecmp(url, "fcgi:", 5) == 0) {
        url += 5;
    }
    else {
        return DECLINED;
    }
    
    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, r->server,
                 "proxy: FCGI: canonicalising URL %s", url);

    err = ap_proxy_canon_netloc(r->pool, &url, NULL, NULL, &host, &port);
    if (err) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "error parsing URL %s: %s", url, err);
        return HTTP_BAD_REQUEST;
    }
        
    apr_snprintf(sport, sizeof(sport), ":%d", port);
        
    if (ap_strchr_c(host, ':')) {
        /* if literal IPv6 address */
        host = apr_pstrcat(r->pool, "[", host, "]", NULL);
    }

    if (apr_table_get(r->notes, "proxy-nocanon")) {
