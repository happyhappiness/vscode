static void *privileges_create_dir_cfg(apr_pool_t *pool, char *dummy)
{
    priv_dir_cfg *cfg = apr_palloc(pool, sizeof(priv_dir_cfg));
    cfg->mode = PRIV_UNSET;
    return cfg;
}