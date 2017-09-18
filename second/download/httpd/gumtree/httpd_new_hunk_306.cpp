void ssl_init_ConfigureServer(server_rec *s,
                              apr_pool_t *p,
                              apr_pool_t *ptemp,
                              SSLSrvConfigRec *sc)
{
    if (sc->enabled) {
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                     "Configuring server for SSL protocol");
        ssl_init_server_ctx(s, p, ptemp, sc);
    }

    if (sc->proxy_enabled) {
        ssl_init_proxy_ctx(s, p, ptemp, sc);
    }
