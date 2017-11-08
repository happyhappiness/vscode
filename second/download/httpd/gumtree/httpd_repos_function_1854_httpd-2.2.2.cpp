static void *create_authz_default_dir_config(apr_pool_t *p, char *d)
{
    authz_default_config_rec *conf = apr_palloc(p, sizeof(*conf));

    conf->authoritative = 1; /* keep the fortress secure by default */
    return conf;
}