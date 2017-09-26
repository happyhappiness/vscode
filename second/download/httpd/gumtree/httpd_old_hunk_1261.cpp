 * Insert an item into the cache.
 * *** Does not catch duplicates!!! ***
 */
void *util_ald_cache_insert(util_ald_cache_t *cache, void *payload)
{
    unsigned long hashval;
    util_cache_node_t *node;

    /* sanity check */
    if (cache == NULL || payload == NULL) {
        return NULL;
    }

    /* check if we are full - if so, try purge */
    if (cache->numentries >= cache->maxentries) {
        util_ald_cache_purge(cache);
        if (cache->numentries >= cache->maxentries) {
            /* if the purge was not effective, we leave now to avoid an overflow */
            return NULL;
        }
    }

    /* should be safe to add an entry */
    if ((node = (util_cache_node_t *)util_ald_alloc(cache, sizeof(util_cache_node_t))) == NULL) {
        return NULL;
    }

    /* Take a copy of the payload before proceeeding. */
    payload = (*cache->copy)(cache, payload);
    if (!payload) {
        util_ald_free(cache, node);
        return NULL;
    }

    /* populate the entry */
    cache->inserts++;
    hashval = (*cache->hash)(payload) % cache->size;
    node->add_time = apr_time_now();
    node->payload = payload;
