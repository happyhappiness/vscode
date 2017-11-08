static void *create_auth_basic_dir_config(apr_pool_t *p, char *d)
{
    auth_basic_config_rec *conf = apr_pcalloc(p, sizeof(*conf));

    conf->dir = d;
    /* Any failures are fatal. */
    conf->authoritative = 1;

    return conf;
}