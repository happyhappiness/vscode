static void *CaseFilterCreateServerConfig(apr_pool_t *p,server_rec *s)
    {
    CaseFilterConfig *pConfig=apr_pcalloc(p,sizeof *pConfig);

    pConfig->bEnabled=0;

    return pConfig;
    }