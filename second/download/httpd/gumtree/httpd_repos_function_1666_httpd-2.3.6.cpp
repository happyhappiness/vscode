static void *create_server_config(apr_pool_t *p, server_rec *s)
{
    serf_server_config_t *ctx = 
        (serf_server_config_t *) apr_pcalloc(p, sizeof(serf_server_config_t));

    ctx->clusters = apr_hash_make(p);

    return ctx;
}