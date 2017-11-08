static void *dbd_merge(apr_pool_t *pool, void *base, void *add) {
    svr_cfg *cfg = apr_pmemdup(pool, add, sizeof(svr_cfg));
    COND_PARAM0(name);
    COND_PARAM0(params);
    COND_PARAM1(persist);
#if APR_HAS_THREADS
    COND_PARAM(nmin, DEFAULT_NMIN);
    COND_PARAM(nkeep, DEFAULT_NKEEP);
    COND_PARAM(nmax, DEFAULT_NMAX);
    COND_PARAM(exptime, DEFAULT_EXPTIME);
#endif
    return cfg;
}