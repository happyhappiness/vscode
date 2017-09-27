
    /* Create a temporary pool to constrain memory use */
    apr_pool_create(&vpool, conn->pool);

    ok = apr_uri_parse(vpool, ocspuri, &uri);
    if (ok != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01939)
                     "stapling_renew_response: Error parsing uri %s",
                      ocspuri);
        rv = FALSE;
        goto done;
    }
    else if (strcmp(uri.scheme, "http")) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01940)
                     "stapling_renew_response: Unsupported uri %s", ocspuri);
        rv = FALSE;
        goto done;
    }

    if (!uri.port) {
