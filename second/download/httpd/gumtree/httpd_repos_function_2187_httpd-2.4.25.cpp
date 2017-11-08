static void *create_scgi_config(apr_pool_t *p, char *dummy)
{
    scgi_config *conf=apr_palloc(p, sizeof(*conf));

    conf->sendfile = NULL; /* === default (off) */
    conf->internal_redirect = NULL; /* === default (on) */

    return conf;
}