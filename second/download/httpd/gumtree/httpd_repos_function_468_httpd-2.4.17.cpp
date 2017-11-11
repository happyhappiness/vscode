static void *merge_forensic_log_scfg(apr_pool_t *p, void *parent, void *new)
{
    fcfg *cfg = apr_pcalloc(p, sizeof *cfg);
    fcfg *pc = parent;
    fcfg *nc = new;

    cfg->logname = apr_pstrdup(p, nc->logname ? nc->logname : pc->logname);
    cfg->fd = NULL;

    return cfg;
}