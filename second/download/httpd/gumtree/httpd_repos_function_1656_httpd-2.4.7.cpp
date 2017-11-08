static void *mkconfig(apr_pool_t *p)
{
    suexec_config_t *cfg = apr_palloc(p, sizeof(suexec_config_t));

    cfg->active = 0;
    return cfg;
}