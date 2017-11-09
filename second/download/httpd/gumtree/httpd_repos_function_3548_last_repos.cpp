void util_ald_destroy_cache(util_ald_cache_t *cache)
{
    unsigned long i;
    util_cache_node_t *p, *q;

    if (cache == NULL)
        return;

    for (i = 0; i < cache->size; ++i) {
        p = cache->nodes[i];
        q = NULL;
        while (p != NULL) {
            q = p->next;
           (*cache->free)(cache, p->payload);
           util_ald_free(cache, p);
           p = q;
        }
    }
    util_ald_free(cache, cache->nodes);
    util_ald_free(cache, cache);
}