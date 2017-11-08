static void *mva_create_server_config(apr_pool_t *p, server_rec *s)
{
    mva_sconf_t *conf;

    conf = (mva_sconf_t *) apr_pcalloc(p, sizeof(mva_sconf_t));
    conf->doc_root = NULL;
    conf->cgi_root = NULL;
    conf->doc_root_mode = VHOST_ALIAS_UNSET;
    conf->cgi_root_mode = VHOST_ALIAS_UNSET;
    return conf;
}