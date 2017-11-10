void *ssl_config_server_merge(apr_pool_t *p, void *basev, void *addv)
{
    SSLSrvConfigRec *base = (SSLSrvConfigRec *)basev;
    SSLSrvConfigRec *add  = (SSLSrvConfigRec *)addv;
    SSLSrvConfigRec *mrg  = ssl_config_server_new(p);

    cfgMerge(mc, NULL);
    cfgMerge(enabled, SSL_ENABLED_UNSET);
    cfgMergeBool(proxy_enabled);
    cfgMergeInt(session_cache_timeout);
    cfgMergeBool(cipher_server_pref);
    cfgMergeBool(insecure_reneg);
    cfgMerge(proxy_ssl_check_peer_expire, SSL_ENABLED_UNSET);
    cfgMerge(proxy_ssl_check_peer_cn, SSL_ENABLED_UNSET);
#ifndef OPENSSL_NO_TLSEXT
    cfgMerge(strict_sni_vhost_check, SSL_ENABLED_UNSET);
#endif
#ifdef HAVE_FIPS
    cfgMergeBool(fips);
#endif
#ifndef OPENSSL_NO_COMP
    cfgMergeBool(compression);
#endif
    cfgMergeBool(session_tickets);

    modssl_ctx_cfg_merge_proxy(base->proxy, add->proxy, mrg->proxy);

    modssl_ctx_cfg_merge_server(base->server, add->server, mrg->server);

    return mrg;
}