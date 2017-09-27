                     NULL);
    cp[strlen(cp)-2] = NUL;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "Creating new SSL context (protocols: %s)", cp);

    if (protocol == SSL_PROTOCOL_SSLV2) {
        method = mctx->pkp ?
            SSLv2_client_method() : /* proxy */
            SSLv2_server_method();  /* server */
        ctx = SSL_CTX_new(method);  /* only SSLv2 is left */
    }
    else {
        method = mctx->pkp ?
            SSLv23_client_method() : /* proxy */
            SSLv23_server_method();  /* server */
        ctx = SSL_CTX_new(method); /* be more flexible */
    }

