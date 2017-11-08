static void *create_authz_groupfile_dir_config(apr_pool_t *p, char *d)
{
    authz_groupfile_config_rec *conf = apr_palloc(p, sizeof(*conf));

    conf->groupfile = NULL;
    conf->authoritative = 1; /* keep the fortress secure by default */
    return conf;
}