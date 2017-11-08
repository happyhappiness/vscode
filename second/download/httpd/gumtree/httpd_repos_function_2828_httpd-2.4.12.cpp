static void *create_authz_dbm_dir_config(apr_pool_t *p, char *d)
{
    authz_dbm_config_rec *conf = apr_palloc(p, sizeof(*conf));

    conf->grpfile = NULL;
    conf->dbmtype = "default";

    return conf;
}