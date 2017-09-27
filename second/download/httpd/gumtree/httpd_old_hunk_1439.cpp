static void ssl_init_ctx_cipher_suite(server_rec *s,
                                      apr_pool_t *p,
                                      apr_pool_t *ptemp,
                                      modssl_ctx_t *mctx)
{
    SSL_CTX *ctx = mctx->ssl_ctx;
    const char *suite = mctx->auth.cipher_suite;

    /*
     *  Configure SSL Cipher Suite
     */
    if (!suite) {
        return;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "Configuring permitted SSL ciphers [%s]",
                 suite);

    if (!SSL_CTX_set_cipher_list(ctx, MODSSL_PCHAR_CAST suite)) {
