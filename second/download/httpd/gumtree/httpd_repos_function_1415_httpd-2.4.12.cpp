static void *create_dbd_config(apr_pool_t *pool, server_rec *s)
{
    svr_cfg *svr = apr_pcalloc(pool, sizeof(svr_cfg));
    dbd_cfg_t *cfg = svr->cfg = apr_pcalloc(pool, sizeof(dbd_cfg_t));

    cfg->server = s;
    cfg->name = no_dbdriver; /* to generate meaningful error messages */
    cfg->params = ""; /* don't risk segfault on misconfiguration */
    cfg->persist = -1;
#if APR_HAS_THREADS
    cfg->nmin = DEFAULT_NMIN;
    cfg->nkeep = DEFAULT_NKEEP;
    cfg->nmax = DEFAULT_NMAX;
    cfg->exptime = DEFAULT_EXPTIME;
#endif
    cfg->queries = apr_hash_make(pool);
    cfg->init_queries = apr_array_make(pool, DEFAULT_SQL_INIT_ARRAY_SIZE,
                                       sizeof(const char *));

    return svr;
}