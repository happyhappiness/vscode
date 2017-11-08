static void ssl_init_server_ctx(server_rec *s,
                                apr_pool_t *p,
                                apr_pool_t *ptemp,
                                SSLSrvConfigRec *sc)
{
    ssl_init_server_check(s, p, ptemp, sc->server);

    ssl_init_ctx(s, p, ptemp, sc->server);

    ssl_init_server_certs(s, p, ptemp, sc->server);
}