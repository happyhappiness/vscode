static void *create_ef_server_conf(apr_pool_t *p, server_rec *s)
{
    ef_server_t *conf;

    conf = (ef_server_t *)apr_pcalloc(p, sizeof(ef_server_t));
    conf->p = p;
    conf->h = apr_hash_make(conf->p);
    return conf;
}