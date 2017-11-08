void util_ald_cache_insert(util_ald_cache_t *cache, void *payload)
{
    int hashval;
    util_cache_node_t *node;

    if (cache == NULL || payload == NULL)
        return;

    cache->inserts++;
    hashval = (*cache->hash)(payload) % cache->size;
    node = (util_cache_node_t *)util_ald_alloc(sizeof(util_cache_node_t));
    node->add_time = apr_time_now();
    node->payload = (*cache->copy)(payload);
    node->next = cache->nodes[hashval];
    cache->nodes[hashval] = node;
    if (++cache->numentries == cache->fullmark) 
        cache->marktime=apr_time_now();
    if (cache->numentries >= cache->maxentries)
        util_ald_cache_purge(cache);
}