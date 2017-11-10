void* cache_pop(cache_cache_t *c)
{
    void *entry;

    if (!c)
        return NULL;

    entry = cache_pq_pop(c->pq);

    if (!entry)
        return NULL;

    c->current_size -= c->size_entry(entry);
    cache_hash_set(c->ht, c->key_entry(entry), CACHE_HASH_KEY_STRING, NULL);

    return entry;
}