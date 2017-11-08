static void *
dialup_dcfg_create(apr_pool_t *p, char *dummy)
{
    dialup_dcfg_t *cfg = apr_palloc(p, sizeof(dialup_dcfg_t));

    cfg->bytes_per_second = 0;

    return cfg;
}