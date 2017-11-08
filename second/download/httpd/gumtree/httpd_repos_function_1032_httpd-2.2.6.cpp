static void *mkconfig(apr_pool_t *p)
{
    spconfig *cfg = apr_pcalloc(p, sizeof(spconfig));

    cfg->enabled = 0;
    cfg->case_only = 0;
    return cfg;
}