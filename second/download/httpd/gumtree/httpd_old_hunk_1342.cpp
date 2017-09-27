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

#ifndef OPENSSL_NO_SSL2
    if (protocol == SSL_PROTOCOL_SSLV2) {
        method = mctx->pkp ?
            SSLv2_client_method() : /* proxy */
            SSLv2_server_method();  /* server */
        ctx = SSL_CTX_new(method);  /* only SSLv2 is left */
    }
    else
#endif
    {
        method = mctx->pkp ?
            SSLv23_client_method() : /* proxy */
            SSLv23_server_method();  /* server */
        ctx = SSL_CTX_new(method); /* be more flexible */
    }

    mctx->ssl_ctx = ctx;

    SSL_CTX_set_options(ctx, SSL_OP_ALL);

    if (!(protocol & SSL_PROTOCOL_SSLV2)) {
        SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2);
    }

    if (!(protocol & SSL_PROTOCOL_SSLV3)) {
        SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv3);
    }

    if (!(protocol & SSL_PROTOCOL_TLSV1)) {
        SSL_CTX_set_options(ctx, SSL_OP_NO_TLSv1);
    }

#ifdef SSL_OP_CIPHER_SERVER_PREFERENCE
    if (sc->cipher_server_pref == TRUE) {
        SSL_CTX_set_options(ctx, SSL_OP_CIPHER_SERVER_PREFERENCE);
    }
#endif

