static void *am_create_conf(apr_pool_t *p, char *dummy)
{
    am_conf_t *conf = apr_pcalloc(p, sizeof(am_conf_t));

    conf->allowed = 0;
    conf->allowed_set = 0;
    return conf;
}