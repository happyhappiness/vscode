void modssl_init_stapling(server_rec *s, apr_pool_t *p, apr_pool_t *ptemp,
                          modssl_ctx_t *mctx)
{
    SSL_CTX *ctx = mctx->ssl_ctx;
    SSLModConfigRec *mc = myModConfig(s);

    if (mc->stapling_cache == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "SSLStapling: no stapling cache available");
        ssl_die();
    }
    /* Set some default values for parameters if they are not set */
    if (mctx->stapling_resptime_skew == UNSET) {
        mctx->stapling_resptime_skew = 60 * 5;
    }
    if (mctx->stapling_cache_timeout == UNSET) {
        mctx->stapling_cache_timeout = 3600;
    }
    if (mctx->stapling_return_errors == UNSET) {
        mctx->stapling_return_errors = TRUE;
    }
    if (mctx->stapling_fake_trylater == UNSET) {
        mctx->stapling_fake_trylater = TRUE;
    }
    if (mctx->stapling_errcache_timeout == UNSET) {
        mctx->stapling_errcache_timeout = 600;
    }
    if (mctx->stapling_responder_timeout == UNSET) {
        mctx->stapling_responder_timeout = 10 * APR_USEC_PER_SEC;
    }
    SSL_CTX_set_tlsext_status_cb(ctx, stapling_cb);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "OCSP stapling initialized");
}