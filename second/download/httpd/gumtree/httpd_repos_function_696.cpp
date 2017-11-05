int ssl_stapling_mutex_init(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    SSLSrvConfigRec *sc = mySrvConfig(s);
    apr_status_t rv;

    if (mc->stapling_mutex || sc->server->stapling_enabled != TRUE) {
        return TRUE;
    }

    if ((rv = ap_global_mutex_create(&mc->stapling_mutex, NULL,
                                     SSL_STAPLING_MUTEX_TYPE, NULL, s,
                                     s->process->pool, 0)) != APR_SUCCESS) {
        return FALSE;
    }

    return TRUE;
}