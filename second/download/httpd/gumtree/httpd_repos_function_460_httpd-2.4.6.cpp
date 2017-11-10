static void *make_forensic_log_scfg(apr_pool_t *p, server_rec *s)
{
    fcfg *cfg = apr_pcalloc(p, sizeof *cfg);

    cfg->logname = NULL;
    cfg->fd = NULL;

    return cfg;
}