static SSLSrvConfigRec *ssl_config_server_new(apr_pool_t *p)
{
    SSLSrvConfigRec *sc = apr_palloc(p, sizeof(*sc));

    sc->mc                     = NULL;
    sc->enabled                = SSL_ENABLED_UNSET;
    sc->proxy_enabled          = UNSET;
    sc->vhost_id               = NULL;  /* set during module init */
    sc->vhost_id_len           = 0;     /* set during module init */
    sc->session_cache_timeout  = UNSET;
    sc->cipher_server_pref     = UNSET;
    sc->insecure_reneg         = UNSET;
    sc->proxy_ssl_check_peer_expire = SSL_ENABLED_UNSET;
    sc->proxy_ssl_check_peer_cn     = SSL_ENABLED_UNSET;
    sc->proxy_ssl_check_peer_name   = SSL_ENABLED_UNSET;
#ifdef HAVE_TLSEXT
    sc->strict_sni_vhost_check = SSL_ENABLED_UNSET;
#endif
#ifdef HAVE_FIPS
    sc->fips                   = UNSET;
#endif
#ifndef OPENSSL_NO_COMP
    sc->compression            = UNSET;
#endif
    sc->session_tickets        = UNSET;

    modssl_ctx_init_proxy(sc, p);

    modssl_ctx_init_server(sc, p);

    return sc;
}