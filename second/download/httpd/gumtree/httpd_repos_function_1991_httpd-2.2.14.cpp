static void *create_authn_alias_svr_config(apr_pool_t *p, server_rec *s)
{

    authn_alias_srv_conf *authcfg;

    authcfg = (authn_alias_srv_conf *) apr_pcalloc(p, sizeof(authn_alias_srv_conf));
    authcfg->alias_rec = apr_hash_make(p);

    return (void *) authcfg;
}