static void *merge_dbd_config(apr_pool_t *pool, void *basev, void *addv)
{
    dbd_cfg_t *base = ((svr_cfg*) basev)->cfg;
    dbd_cfg_t *add = ((svr_cfg*) addv)->cfg;
    svr_cfg *svr = apr_pcalloc(pool, sizeof(svr_cfg));
    dbd_cfg_t *new = svr->cfg = apr_pcalloc(pool, sizeof(dbd_cfg_t));

    new->server = add->server;
    new->name = (add->name != no_dbdriver) ? add->name : base->name;
    new->params = strcmp(add->params, "") ? add->params : base->params;
    new->persist = (add->persist != -1) ? add->persist : base->persist;
#if APR_HAS_THREADS
    new->nmin = (add->set&NMIN_SET) ? add->nmin : base->nmin;
    new->nkeep = (add->set&NKEEP_SET) ? add->nkeep : base->nkeep;
    new->nmax = (add->set&NMAX_SET) ? add->nmax : base->nmax;
    new->exptime = (add->set&EXPTIME_SET) ? add->exptime : base->exptime;
#endif
    new->queries = apr_hash_overlay(pool, add->queries, base->queries);
    new->init_queries = apr_array_append(pool, add->init_queries,
                                         base->init_queries);

    return svr;
}