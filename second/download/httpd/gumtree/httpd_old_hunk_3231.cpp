    certinfo *cinf = NULL;
    OCSP_RESPONSE *rsp = NULL;
    int rv;
    BOOL ok;

    if (sc->server->stapling_enabled != TRUE) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "stapling_cb: OCSP Stapling disabled");
        return SSL_TLSEXT_ERR_NOACK;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "stapling_cb: OCSP Stapling callback called");

    cinf = stapling_get_cert_info(s, mctx, ssl);
    if (cinf == NULL) {
        return SSL_TLSEXT_ERR_NOACK;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "stapling_cb: retrieved cached certificate data");

    /* Check to see if we already have a response for this certificate */
    stapling_mutex_on(s);

    rv = stapling_get_cached_response(s, &rsp, &ok, cinf, conn->pool);
