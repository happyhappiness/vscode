    int protocol = mctx->protocol;

    /*
     *  Create the new per-server SSL context
     */
    if (protocol == SSL_PROTOCOL_NONE) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                "No SSL protocols available [hint: SSLProtocol]");
        ssl_die();
    }

    cp = apr_pstrcat(p,
                     (protocol & SSL_PROTOCOL_SSLV2 ? "SSLv2, " : ""),
                     (protocol & SSL_PROTOCOL_SSLV3 ? "SSLv3, " : ""),
                     (protocol & SSL_PROTOCOL_TLSV1 ? "TLSv1, " : ""),
                     NULL);
    cp[strlen(cp)-2] = NUL;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "Creating new SSL context (protocols: %s)", cp);

    if (protocol == SSL_PROTOCOL_SSLV2) {
        method = mctx->pkp ?
            SSLv2_client_method() : /* proxy */
            SSLv2_server_method();  /* server */
        ctx = SSL_CTX_new(method);  /* only SSLv2 is left */
