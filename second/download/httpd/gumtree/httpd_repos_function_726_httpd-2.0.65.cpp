static SSLSrvConfigRec *ssl_config_server_new(apr_pool_t *p)
{
    SSLSrvConfigRec *sc = apr_palloc(p, sizeof(*sc));

    sc->mc                     = NULL;
    sc->enabled                = UNSET;
    sc->proxy_enabled          = UNSET;
    sc->vhost_id               = NULL;  /* set during module init */
    sc->vhost_id_len           = 0;     /* set during module init */
    sc->session_cache_timeout  = UNSET;
    sc->cipher_server_pref     = UNSET;
    sc->insecure_reneg         = UNSET;

    modssl_ctx_init_proxy(sc, p);

    modssl_ctx_init_server(sc, p);

    return sc;
}