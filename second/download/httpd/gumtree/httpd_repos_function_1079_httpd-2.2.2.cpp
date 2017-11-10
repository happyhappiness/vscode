static void *mva_merge_server_config(apr_pool_t *p, void *parentv, void *childv)
{
    mva_sconf_t *parent = (mva_sconf_t *) parentv;
    mva_sconf_t *child = (mva_sconf_t *) childv;
    mva_sconf_t *conf;

    conf = (mva_sconf_t *) apr_pcalloc(p, sizeof(*conf));
    if (child->doc_root_mode == VHOST_ALIAS_UNSET) {
        conf->doc_root_mode = parent->doc_root_mode;
        conf->doc_root = parent->doc_root;
    }
    else {
        conf->doc_root_mode = child->doc_root_mode;
        conf->doc_root = child->doc_root;
    }
    if (child->cgi_root_mode == VHOST_ALIAS_UNSET) {
        conf->cgi_root_mode = parent->cgi_root_mode;
        conf->cgi_root = parent->cgi_root;
    }
    else {
        conf->cgi_root_mode = child->cgi_root_mode;
        conf->cgi_root = child->cgi_root;
    }
    return conf;
}