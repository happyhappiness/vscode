static void *create_authn_dbm_dir_config(apr_pool_t *p, char *d)
{
    authn_dbm_config_rec *conf = apr_palloc(p, sizeof(*conf));

    conf->pwfile = NULL;
    conf->dbmtype = "default";

    return conf;
}