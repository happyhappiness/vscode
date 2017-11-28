static void
setSessionCallbacks(SSL_CTX *ctx)
{
    if (SslSessionCache) {
        SSL_CTX_set_session_cache_mode(ctx, SSL_SESS_CACHE_SERVER|SSL_SESS_CACHE_NO_INTERNAL);
        SSL_CTX_sess_set_new_cb(ctx, store_session_cb);
        SSL_CTX_sess_set_remove_cb(ctx, remove_session_cb);
        SSL_CTX_sess_set_get_cb(ctx, get_session_cb);
    }
}