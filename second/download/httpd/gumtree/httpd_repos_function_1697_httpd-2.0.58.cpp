static void *create_auth_dir_config(apr_pool_t *p, char *d)
{
    auth_config_rec *conf = apr_palloc(p, sizeof(*conf));

    conf->auth_pwfile = NULL;     /* just to illustrate the default really */
    conf->auth_grpfile = NULL;    /* unless you have a broken HP cc */
    conf->auth_authoritative = 1; /* keep the fortress secure by default */
    return conf;
}