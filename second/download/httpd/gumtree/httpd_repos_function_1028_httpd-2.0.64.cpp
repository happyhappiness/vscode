static void store_cache_string(cache *c, const char *res, cacheentry *ce)
{
    int i;
    int j;
    cachelist *l;
    cacheentry *e;
    cachetlbentry *t;
    int found_list;

#if APR_HAS_THREADS
    apr_thread_mutex_lock(c->lock);
#endif

    found_list = 0;
    /* first try to edit an existing entry */
    for (i = 0; i < c->lists->nelts; i++) {
        l = &(((cachelist *)c->lists->elts)[i]);
        if (strcmp(l->resource, res) == 0) {
            found_list = 1;

            e = cache_tlb_lookup((cachetlbentry *)l->tlb->elts,
                                 (cacheentry *)l->entries->elts, ce->key);
            if (e != NULL) {
                e->time  = ce->time;
                e->value = apr_pstrdup(c->pool, ce->value);
#if APR_HAS_THREADS
                apr_thread_mutex_unlock(c->lock);
#endif
                return;
            }

            for (j = 0; j < l->entries->nelts; j++) {
                e = &(((cacheentry *)l->entries->elts)[j]);
                if (strcmp(e->key, ce->key) == 0) {
                    e->time  = ce->time;
                    e->value = apr_pstrdup(c->pool, ce->value);
                    cache_tlb_replace((cachetlbentry *)l->tlb->elts,
                                      (cacheentry *)l->entries->elts, e);
#if APR_HAS_THREADS
                    apr_thread_mutex_unlock(c->lock);
#endif
                    return;
                }
            }
        }
    }

    /* create a needed new list */
    if (!found_list) {
        l = apr_array_push(c->lists);
        l->resource = apr_pstrdup(c->pool, res);
        l->entries  = apr_array_make(c->pool, 2, sizeof(cacheentry));
        l->tlb      = apr_array_make(c->pool, CACHE_TLB_ROWS,
                                    sizeof(cachetlbentry));
        for (i=0; i<CACHE_TLB_ROWS; ++i) {
            t = &((cachetlbentry *)l->tlb->elts)[i];
                for (j=0; j<CACHE_TLB_COLS; ++j)
                    t->t[j] = -1;
        }
    }

    /* create the new entry */
    for (i = 0; i < c->lists->nelts; i++) {
        l = &(((cachelist *)c->lists->elts)[i]);
        if (strcmp(l->resource, res) == 0) {
            e = apr_array_push(l->entries);
            e->time  = ce->time;
            e->key   = apr_pstrdup(c->pool, ce->key);
            e->value = apr_pstrdup(c->pool, ce->value);
            cache_tlb_replace((cachetlbentry *)l->tlb->elts,
                              (cacheentry *)l->entries->elts, e);
#if APR_HAS_THREADS
            apr_thread_mutex_unlock(c->lock);
#endif
            return;
        }
    }

    /* not reached, but when it is no problem... */
#if APR_HAS_THREADS
    apr_thread_mutex_unlock(c->lock);
#endif
    return;
}