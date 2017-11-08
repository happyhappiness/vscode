static cacheentry *retrieve_cache_string(cache *c, const char *res, char *key)
{
    int i;
    int j;
    cachelist *l;
    cacheentry *e;

#if APR_HAS_THREADS
    apr_thread_mutex_lock(c->lock);
#endif

    for (i = 0; i < c->lists->nelts; i++) {
        l = &(((cachelist *)c->lists->elts)[i]);
        if (strcmp(l->resource, res) == 0) {

            e = cache_tlb_lookup((cachetlbentry *)l->tlb->elts,
                                 (cacheentry *)l->entries->elts, key);
            if (e != NULL) {
#if APR_HAS_THREADS
                apr_thread_mutex_unlock(c->lock);
#endif
                return e;
            }

            for (j = 0; j < l->entries->nelts; j++) {
                e = &(((cacheentry *)l->entries->elts)[j]);
                if (strcmp(e->key, key) == 0) {
#if APR_HAS_THREADS
                    apr_thread_mutex_unlock(c->lock);
#endif
                    return e;
                }
            }
        }
    }
#if APR_HAS_THREADS
    apr_thread_mutex_unlock(c->lock);
#endif
    return NULL;
}