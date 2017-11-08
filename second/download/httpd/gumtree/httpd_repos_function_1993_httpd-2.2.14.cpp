static void *create_authn_anon_dir_config(apr_pool_t *p, char *d)
{
    authn_anon_config_rec *conf = apr_palloc(p, sizeof(*conf));

    /* just to illustrate the defaults really. */
    conf->users = NULL;

    conf->nouserid = 0;
    conf->anyuserid = 0;
    conf->logemail = 1;
    conf->verifyemail = 0;
    conf->mustemail = 1;
    return conf;
}