void *ssl_config_server_merge(apr_pool_t *p, void *basev, void *addv)
{
    SSLSrvConfigRec *base = (SSLSrvConfigRec *)basev;
    SSLSrvConfigRec *add  = (SSLSrvConfigRec *)addv;
    SSLSrvConfigRec *mrg  = ssl_config_server_new(p);

    cfgMerge(mc, NULL);
    cfgMergeBool(enabled);
    cfgMergeBool(proxy_enabled);
    cfgMergeInt(session_cache_timeout);
    cfgMergeBool(insecure_reneg);

    modssl_ctx_cfg_merge_proxy(base->proxy, add->proxy, mrg->proxy);

    modssl_ctx_cfg_merge_server(base->server, add->server, mrg->server);

    return mrg;
}