    else {
        if (*scheme == 'h')
            proxy_function = "HTTP";
        else
            proxy_function = "FTP";
    }
    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, r->server,
                 "proxy: HTTP: serving URL %s", url);


    /* create space for state information */
    if ((status = ap_proxy_acquire_connection(proxy_function, &backend,
                                              worker, r->server)) != OK)
        goto cleanup;
