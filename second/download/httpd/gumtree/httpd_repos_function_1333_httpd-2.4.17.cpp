static void *create_config(apr_pool_t *p, server_rec *s)
{
    cache_socache_conf *conf = apr_pcalloc(p, sizeof(cache_socache_conf));

    return conf;
}