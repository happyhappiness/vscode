static void ssl_init_proxy_ctx(server_rec *s,
                               apr_pool_t *p,
                               apr_pool_t *ptemp,
                               SSLSrvConfigRec *sc)
{
    ssl_init_ctx(s, p, ptemp, sc->proxy);

    ssl_init_proxy_certs(s, p, ptemp, sc->proxy);
}