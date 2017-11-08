static void *dbd_merge(apr_pool_t *pool, void *BASE, void *ADD) {
    svr_cfg *base = (svr_cfg*) BASE;
    svr_cfg *add = (svr_cfg*) ADD;
    svr_cfg *cfg = apr_pcalloc(pool, sizeof(svr_cfg));
    cfg->name = (add->name != no_dbdriver) ? add->name : base->name;
    cfg->params = strcmp(add->params, "") ? add->params : base->params;
    cfg->persist = (add->persist == -1) ? base->persist : add->persist;
#if APR_HAS_THREADS
    cfg->nmin = (add->set&NMIN_SET) ? add->nmin : base->nmin;
    cfg->nkeep = (add->set&NKEEP_SET) ? add->nkeep : base->nkeep;
    cfg->nmax = (add->set&NMAX_SET) ? add->nmax : base->nmax;
    cfg->exptime = (add->set&EXPTIME_SET) ? add->exptime : base->exptime;
#endif
    cfg->set = add->set | base->set;
    cfg->prepared = (add->prepared != NULL) ? add->prepared : base->prepared;
    return (void*) cfg;
}