static void *create_authn_file_dir_config(apr_pool_t *p, char *d)
{
    authn_file_config_rec *conf = apr_palloc(p, sizeof(*conf));

    conf->pwfile = NULL;     /* just to illustrate the default really */
    return conf;
}