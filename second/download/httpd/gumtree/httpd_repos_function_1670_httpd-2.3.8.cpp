static void * merge_server_config(apr_pool_t *p, void *basev, void *overridesv)
{
    serf_server_config_t *ctx = apr_pcalloc(p, sizeof(serf_server_config_t));
    serf_server_config_t *base = (serf_server_config_t *) basev;
    serf_server_config_t *overrides = (serf_server_config_t *) overridesv;
    
    ctx->clusters = apr_hash_overlay(p, base->clusters, overrides->clusters);
    return ctx;
}