static void ssl_init_ctx_cipher_suite(server_rec *s,
                                      apr_pool_t *p,
                                      apr_pool_t *ptemp,
                                      modssl_ctx_t *mctx)
{
    SSL_CTX *ctx = mctx->ssl_ctx;
    const char *suite;

    /*
     *  Configure SSL Cipher Suite. Always disable NULL and export ciphers,
     *  see also ssl_engine_config.c:ssl_cmd_SSLCipherSuite().
     *  OpenSSL's SSL_DEFAULT_CIPHER_LIST includes !aNULL:!eNULL from 0.9.8f,
     *  and !EXP from 0.9.8zf/1.0.1m/1.0.2a, so prepend them while we support
     *  earlier versions.
     */
    suite = mctx->auth.cipher_suite ? mctx->auth.cipher_suite :
            apr_pstrcat(ptemp, "!aNULL:!eNULL:!EXP:", SSL_DEFAULT_CIPHER_LIST,
                        NULL);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "Configuring permitted SSL ciphers [%s]",
                 suite);

    if (!SSL_CTX_set_cipher_list(ctx, MODSSL_PCHAR_CAST suite)) {
