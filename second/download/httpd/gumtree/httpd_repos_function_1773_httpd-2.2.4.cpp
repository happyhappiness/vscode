void *util_ald_cache_fetch(util_ald_cache_t *cache, void *payload)
{
    unsigned long hashval;
    util_cache_node_t *p;

    if (cache == NULL)
        return NULL;

    cache->fetches++;

    hashval = (*cache->hash)(payload) % cache->size;
    for (p = cache->nodes[hashval];
         p && !(*cache->compare)(p->payload, payload);
    p = p->next) ;

    if (p != NULL) {
        cache->hits++;
        return p->payload;
    }
    else {
        return NULL;
    }
}