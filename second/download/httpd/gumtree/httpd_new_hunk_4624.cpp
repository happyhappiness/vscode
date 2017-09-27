
    if (!(protocol & SSL_PROTOCOL_TLSV1_2)) {
        SSL_CTX_set_options(ctx, SSL_OP_NO_TLSv1_2);
    }
#endif

#else /* #if OPENSSL_VERSION_NUMBER < 0x10100000L */
    /* We first determine the maximum protocol version we should provide */
    if (protocol & SSL_PROTOCOL_TLSV1_2) {
        prot = TLS1_2_VERSION;
    } else if (protocol & SSL_PROTOCOL_TLSV1_1) {
        prot = TLS1_1_VERSION;
    } else if (protocol & SSL_PROTOCOL_TLSV1) {
        prot = TLS1_VERSION;
#ifndef OPENSSL_NO_SSL3
    } else if (protocol & SSL_PROTOCOL_SSLV3) {
        prot = SSL3_VERSION;
#endif
    } else {
        SSL_CTX_free(ctx);
        mctx->ssl_ctx = NULL;
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(03378)
                "No SSL protocols available [hint: SSLProtocol]");
        return ssl_die(s);
    }
    SSL_CTX_set_max_proto_version(ctx, prot);

    /* Next we scan for the minimal protocol version we should provide,
     * but we do not allow holes between max and min */
    if (prot == TLS1_2_VERSION && protocol & SSL_PROTOCOL_TLSV1_1) {
        prot = TLS1_1_VERSION;
    }
    if (prot == TLS1_1_VERSION && protocol & SSL_PROTOCOL_TLSV1) {
        prot = TLS1_VERSION;
    }
#ifndef OPENSSL_NO_SSL3
    if (prot == TLS1_VERSION && protocol & SSL_PROTOCOL_SSLV3) {
        prot = SSL3_VERSION;
    }
#endif
    SSL_CTX_set_min_proto_version(ctx, prot);
#endif /* if OPENSSL_VERSION_NUMBER < 0x10100000L */

#ifdef SSL_OP_CIPHER_SERVER_PREFERENCE
    if (sc->cipher_server_pref == TRUE) {
        SSL_CTX_set_options(ctx, SSL_OP_CIPHER_SERVER_PREFERENCE);
    }
#endif

