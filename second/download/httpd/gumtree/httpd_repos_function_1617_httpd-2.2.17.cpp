static void *create_scgi_config(apr_pool_t *p, char *dummy)
{
    scgi_config *conf=apr_palloc(p, sizeof(*conf));

    conf->sendfile = NULL;
    conf->internal_redirect = -1;

    return conf;
}