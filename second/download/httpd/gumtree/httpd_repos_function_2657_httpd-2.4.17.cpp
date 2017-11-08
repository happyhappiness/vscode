static void *filter_config(apr_pool_t *pool, char *x)
{
    mod_filter_cfg *cfg = apr_palloc(pool, sizeof(mod_filter_cfg));
    cfg->live_filters = apr_hash_make(pool);
    cfg->chain = NULL;
    return cfg;
}