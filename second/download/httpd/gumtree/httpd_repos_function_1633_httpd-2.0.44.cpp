static void *create_anon_auth_dir_config(apr_pool_t *p, char *d)
{
    anon_auth_config_rec *conf = apr_palloc(p, sizeof(*conf));

    /* just to illustrate the defaults really. */
    conf->anon_auth_passwords = NULL;

    conf->anon_auth_nouserid = 0;
    conf->anon_auth_logemail = 1;
    conf->anon_auth_verifyemail = 0;
    conf->anon_auth_mustemail = 1;
    conf->anon_auth_authoritative = 0;
    return conf;
}