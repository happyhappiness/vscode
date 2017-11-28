void
Security::SetSessionCacheCallbacks(Security::ContextPointer &ctx)
{
    if (SessionCache) {
        SSL_CTX_set_session_cache_mode(ctx.get(), SSL_SESS_CACHE_SERVER|SSL_SESS_CACHE_NO_INTERNAL);
        SSL_CTX_sess_set_new_cb(ctx.get(), store_session_cb);
        SSL_CTX_sess_set_remove_cb(ctx.get(), remove_session_cb);
        SSL_CTX_sess_set_get_cb(ctx.get(), get_session_cb);
    }
}