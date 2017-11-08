void util_ald_cache_purge(util_ald_cache_t *cache)
{
    int i;
    util_cache_node_t *p, *q;
    apr_time_t t;

    if (!cache)
        return;
  
    cache->last_purge = apr_time_now();
    cache->npurged = 0;
    cache->numpurges++;

    for (i=0; i < cache->size; ++i) {
        p = cache->nodes[i];
        while (p != NULL) {
            if (p->add_time < cache->marktime) {
	        q = p->next;
	        (*cache->free)(p->payload);
	        util_ald_free(p);
	        cache->numentries--;
	        cache->npurged++;
	        p = q;
            }
            else {
	        p = p->next;
            }
        }
    }

    t = apr_time_now();
    cache->avg_purgetime = 
         ((t - cache->last_purge) + (cache->avg_purgetime * (cache->numpurges-1))) / 
         cache->numpurges;
}