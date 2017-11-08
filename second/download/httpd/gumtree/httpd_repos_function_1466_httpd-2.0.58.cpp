void util_ald_cache_remove(util_ald_cache_t *cache, void *payload)
{
    int hashval;
    util_cache_node_t *p, *q;
  
    if (cache == NULL)
        return;

    cache->removes++;
    hashval = (*cache->hash)(payload) % cache->size;
    for (p = cache->nodes[hashval], q=NULL;
         p && !(*cache->compare)(p->payload, payload);
         p = p->next) {
         q = p;
    }

    /* If p is null, it means that we couldn't find the node, so just return */
    if (p == NULL)
        return;

    if (q == NULL) {
        /* We found the node, and it's the first in the list */
        cache->nodes[hashval] = p->next;
    }
    else {
        /* We found the node and it's not the first in the list */
        q->next = p->next;
    }
    (*cache->free)(cache, p->payload);
    util_ald_free(cache, p);
    cache->numentries--;
}