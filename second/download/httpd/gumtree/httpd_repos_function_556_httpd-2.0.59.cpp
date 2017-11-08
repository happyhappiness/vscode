static void ssl_init_ctx_callbacks(server_rec *s,
                                   apr_pool_t *p,
                                   apr_pool_t *ptemp,
                                   modssl_ctx_t *mctx)
{
    SSL_CTX *ctx = mctx->ssl_ctx;

    SSL_CTX_set_tmp_rsa_callback(ctx, ssl_callback_TmpRSA);
    SSL_CTX_set_tmp_dh_callback(ctx,  ssl_callback_TmpDH);

    if (s->loglevel >= APLOG_DEBUG) {
        /* this callback only logs if LogLevel >= info */
        SSL_CTX_set_info_callback(ctx, ssl_callback_LogTracingState);
    }
}