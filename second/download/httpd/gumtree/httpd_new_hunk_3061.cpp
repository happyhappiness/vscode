    scheme = apr_pstrndup(p, url, u - url);
    /* scheme is lowercase */
    ap_str_tolower(scheme);
    /* is it for us? */
    if (strcmp(scheme, "https") == 0) {
        if (!ap_proxy_ssl_enable(NULL)) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01112)
                          "HTTPS: declining URL %s (mod_ssl not configured?)",
                          url);
            return DECLINED;
        }
        is_ssl = 1;
        proxy_function = "HTTPS";
    }
    else if (!(strcmp(scheme, "http") == 0 || (strcmp(scheme, "ftp") == 0 && proxyname))) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01113) "HTTP: declining URL %s",
                      url);
        return DECLINED; /* only interested in HTTP, or FTP via proxy */
    }
    else {
        if (*scheme == 'h')
            proxy_function = "HTTP";
        else
            proxy_function = "FTP";
    }
    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, "HTTP: serving URL %s", url);


    /* create space for state information */
    if ((status = ap_proxy_acquire_connection(proxy_function, &backend,
                                              worker, r->server)) != OK)
        goto cleanup;
