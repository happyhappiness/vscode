int ssl_stapling_mutex_reinit(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);

    if (mc->stapling_cache_mutex != NULL
        && stapling_mutex_reinit_helper(s, p, &mc->stapling_cache_mutex,
                                        SSL_STAPLING_CACHE_MUTEX_TYPE) == FALSE) {
        return FALSE;
    }

    if (mc->stapling_refresh_mutex != NULL
        && stapling_mutex_reinit_helper(s, p, &mc->stapling_refresh_mutex,
                                        SSL_STAPLING_REFRESH_MUTEX_TYPE) == FALSE) {
        return FALSE;
    }

    return TRUE;
}