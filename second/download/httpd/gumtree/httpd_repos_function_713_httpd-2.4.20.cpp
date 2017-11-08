static int ssl_stapling_mutex_init(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    SSLSrvConfigRec *sc = mySrvConfig(s);
    apr_status_t rv;

    /* already init or stapling not enabled? */
    if (mc->stapling_refresh_mutex || sc->server->stapling_enabled != TRUE) {
        return TRUE;
    }

    /* need a cache mutex? */
    if (mc->stapling_cache->flags & AP_SOCACHE_FLAG_NOTMPSAFE) {
        if ((rv = ap_global_mutex_create(&mc->stapling_cache_mutex, NULL,
                                         SSL_STAPLING_CACHE_MUTEX_TYPE, NULL, s,
                                         s->process->pool, 0)) != APR_SUCCESS) {
            return FALSE;
        }
    }

    /* always need stapling_refresh_mutex */
    if ((rv = ap_global_mutex_create(&mc->stapling_refresh_mutex, NULL,
                                     SSL_STAPLING_REFRESH_MUTEX_TYPE, NULL, s,
                                     s->process->pool, 0)) != APR_SUCCESS) {
        return FALSE;
    }

    return TRUE;
}