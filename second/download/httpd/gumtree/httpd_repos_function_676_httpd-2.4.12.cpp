static void ssl_init_ctx_session_cache(server_rec *s,
                                       apr_pool_t *p,
                                       apr_pool_t *ptemp,
                                       modssl_ctx_t *mctx)
{
    SSL_CTX *ctx = mctx->ssl_ctx;
    SSLModConfigRec *mc = myModConfig(s);

    SSL_CTX_set_session_cache_mode(ctx, mc->sesscache_mode);

    if (mc->sesscache) {
        SSL_CTX_sess_set_new_cb(ctx,    ssl_callback_NewSessionCacheEntry);
        SSL_CTX_sess_set_get_cb(ctx,    ssl_callback_GetSessionCacheEntry);
        SSL_CTX_sess_set_remove_cb(ctx, ssl_callback_DelSessionCacheEntry);
    }
}