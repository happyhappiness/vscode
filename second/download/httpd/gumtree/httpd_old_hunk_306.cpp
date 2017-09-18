void ssl_init_ConfigureServer(server_rec *s,
                              apr_pool_t *p,
                              apr_pool_t *ptemp,
                              SSLSrvConfigRec *sc)
{
    if (sc->enabled) {
        ssl_log(s, SSL_LOG_INFO|SSL_INIT,
                "Configuring server for SSL protocol");
        ssl_init_server_ctx(s, p, ptemp, sc);
    }

    if (sc->proxy_enabled) {
        ssl_init_proxy_ctx(s, p, ptemp, sc);
    }
