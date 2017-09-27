                     NULL);
    cp[strlen(cp)-2] = NUL;

    ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, s,
                 "Creating new SSL context (protocols: %s)", cp);

#if OPENSSL_VERSION_NUMBER < 0x10100000L
#ifndef OPENSSL_NO_SSL3
    if (protocol == SSL_PROTOCOL_SSLV3) {
        method = mctx->pkp ?
            SSLv3_client_method() : /* proxy */
            SSLv3_server_method();  /* server */
    }
