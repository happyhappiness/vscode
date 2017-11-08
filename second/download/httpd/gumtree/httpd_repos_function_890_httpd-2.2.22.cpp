void ssl_scache_init(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);

    /*
     * Warn the user that he should use the session cache.
     * But we can operate without it, of course.
     */
    if (mc->nSessionCacheMode == SSL_SCMODE_UNSET) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                     "Init: Session Cache is not configured "
                     "[hint: SSLSessionCache]");
        mc->nSessionCacheMode = SSL_SCMODE_NONE;
        return;
    }

    if (mc->nSessionCacheMode == SSL_SCMODE_DBM)
        ssl_scache_dbm_init(s, p);
#ifdef HAVE_DISTCACHE
    else if (mc->nSessionCacheMode == SSL_SCMODE_DC)
        ssl_scache_dc_init(s, p);
#endif
    else if (mc->nSessionCacheMode == SSL_SCMODE_SHMCB) {
        void *data;
        const char *userdata_key = "ssl_scache_init";

        apr_pool_userdata_get(&data, userdata_key, s->process->pool);
        if (!data) {
            apr_pool_userdata_set((const void *)1, userdata_key,
                                  apr_pool_cleanup_null, s->process->pool);
            return;
        }
        ssl_scache_shmcb_init(s, p);
    }
}