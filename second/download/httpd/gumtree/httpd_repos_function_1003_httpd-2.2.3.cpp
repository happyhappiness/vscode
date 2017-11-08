static void *dbd_cfg(apr_pool_t *p, server_rec *x)
{
    svr_cfg *svr = (svr_cfg*) apr_pcalloc(p, sizeof(svr_cfg));
    svr->params = ""; /* don't risk segfault on misconfiguration */
    svr->name = no_dbdriver; /* to generate meaningful error messages */
    svr->persist = -1;
#if APR_HAS_THREADS
    svr->nmin = DEFAULT_NMIN;
    svr->nkeep = DEFAULT_NKEEP;
    svr->nmax = DEFAULT_NMAX;
    svr->exptime = DEFAULT_EXPTIME;
#endif
    return svr;
}