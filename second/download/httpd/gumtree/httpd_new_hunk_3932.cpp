        goto done;
    }

    /* Create a temporary pool to constrain memory use */
    apr_pool_create(&vpool, conn->pool);

    if (apr_uri_parse(vpool, ocspuri, &uri) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01939)
                     "stapling_renew_response: Error parsing uri %s",
                      ocspuri);
        rv = FALSE;
        goto done;
    }
