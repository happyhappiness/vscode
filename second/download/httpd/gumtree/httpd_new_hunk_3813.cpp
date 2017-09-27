    const char *suite;

    /*
     *  Configure SSL Cipher Suite. Always disable NULL and export ciphers,
     *  see also ssl_engine_config.c:ssl_cmd_SSLCipherSuite().
     *  OpenSSL's SSL_DEFAULT_CIPHER_LIST includes !aNULL:!eNULL from 0.9.8f,
     *  and !EXP from 0.9.8zf/1.0.1m/1.0.2a, so append them while we support
     *  earlier versions.
     */
    suite = mctx->auth.cipher_suite ? mctx->auth.cipher_suite :
            apr_pstrcat(ptemp, SSL_DEFAULT_CIPHER_LIST, ":!aNULL:!eNULL:!EXP",
                        NULL);

    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
                 "Configuring permitted SSL ciphers [%s]",
                 suite);

