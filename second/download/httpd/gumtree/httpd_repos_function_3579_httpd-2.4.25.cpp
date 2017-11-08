static void *create_authz_core_svr_config(apr_pool_t *p, server_rec *s)
{
    authz_core_srv_conf *authcfg;

    authcfg = apr_pcalloc(p, sizeof(*authcfg));
    authcfg->alias_rec = apr_hash_make(p);

    return (void *)authcfg;
}