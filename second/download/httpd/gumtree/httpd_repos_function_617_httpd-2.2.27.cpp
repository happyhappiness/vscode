static void ssl_init_ctx_session_cache(server_rec *s,
                                       apr_pool_t *p,
                                       apr_pool_t *ptemp,
                                       modssl_ctx_t *mctx)
{
    SSL_CTX *ctx = mctx->ssl_ctx;
    SSLModConfigRec *mc = myModConfig(s);
    long cache_mode = SSL_SESS_CACHE_OFF;
    if (mc->nSessionCacheMode != SSL_SCMODE_NONE) {
        /* SSL_SESS_CACHE_NO_INTERNAL will force OpenSSL
         * to ignore process local-caching and
         * to always get/set/delete sessions using mod_ssl's callbacks.
         */
        cache_mode = SSL_SESS_CACHE_SERVER|SSL_SESS_CACHE_NO_INTERNAL;
    }

    SSL_CTX_set_session_cache_mode(ctx, cache_mode);

    SSL_CTX_sess_set_new_cb(ctx,    ssl_callback_NewSessionCacheEntry);
    SSL_CTX_sess_set_get_cb(ctx,    ssl_callback_GetSessionCacheEntry);
    SSL_CTX_sess_set_remove_cb(ctx, ssl_callback_DelSessionCacheEntry);
}