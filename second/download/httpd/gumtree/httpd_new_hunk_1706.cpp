
    if (strncasecmp(url, SCHEME "://", sizeof(SCHEME) + 2)) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "proxy: " PROXY_FUNCTION ": declining URL %s", url);
        return DECLINED;
    }

    /* Create space for state information */
    status = ap_proxy_acquire_connection(PROXY_FUNCTION, &backend, worker,
                                         r->server);
    if (status != OK) {
        goto cleanup;
    }
