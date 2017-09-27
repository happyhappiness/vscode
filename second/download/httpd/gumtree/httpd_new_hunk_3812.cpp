        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02231)
                "No SSL protocols available [hint: SSLProtocol]");
        return ssl_die(s);
    }

    cp = apr_pstrcat(p,
#ifndef OPENSSL_NO_SSL3
                     (protocol & SSL_PROTOCOL_SSLV3 ? "SSLv3, " : ""),
#endif
                     (protocol & SSL_PROTOCOL_TLSV1 ? "TLSv1, " : ""),
#ifdef HAVE_TLSV1_X
                     (protocol & SSL_PROTOCOL_TLSV1_1 ? "TLSv1.1, " : ""),
                     (protocol & SSL_PROTOCOL_TLSV1_2 ? "TLSv1.2, " : ""),
#endif
                     NULL);
    cp[strlen(cp)-2] = NUL;

    ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, s,
                 "Creating new SSL context (protocols: %s)", cp);

#ifndef OPENSSL_NO_SSL3
    if (protocol == SSL_PROTOCOL_SSLV3) {
        method = mctx->pkp ?
            SSLv3_client_method() : /* proxy */
            SSLv3_server_method();  /* server */
    }
    else
#endif
    if (protocol == SSL_PROTOCOL_TLSV1) {
        method = mctx->pkp ?
            TLSv1_client_method() : /* proxy */
            TLSv1_server_method();  /* server */
    }
#ifdef HAVE_TLSV1_X
    else if (protocol == SSL_PROTOCOL_TLSV1_1) {
