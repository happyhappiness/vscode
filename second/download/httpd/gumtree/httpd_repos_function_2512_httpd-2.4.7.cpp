static void *CaseFilterInCreateServerConfig(apr_pool_t *p, server_rec *s)
{
    CaseFilterInConfig *pConfig = apr_pcalloc(p, sizeof *pConfig);

    pConfig->bEnabled = 0;

    return pConfig;
}