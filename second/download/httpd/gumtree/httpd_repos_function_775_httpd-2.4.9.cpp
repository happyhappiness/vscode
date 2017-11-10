void *ssl_config_server_create(apr_pool_t *p, server_rec *s)
{
    SSLSrvConfigRec *sc = ssl_config_server_new(p);

    sc->mc = ssl_config_global_create(s);

    return sc;
}