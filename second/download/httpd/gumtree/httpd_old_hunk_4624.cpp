
    if (!(protocol & SSL_PROTOCOL_TLSV1_2)) {
        SSL_CTX_set_options(ctx, SSL_OP_NO_TLSv1_2);
    }
#endif

#ifdef SSL_OP_CIPHER_SERVER_PREFERENCE
    if (sc->cipher_server_pref == TRUE) {
        SSL_CTX_set_options(ctx, SSL_OP_CIPHER_SERVER_PREFERENCE);
    }
#endif

