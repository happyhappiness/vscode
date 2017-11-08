void cache_insert(cache_cache_t* c, void *entry)
{
    void *ejected = NULL;
    long priority;

    c->set_pri(c->queue_clock, entry);
    /* FIX: check if priority of bottom item is greater than inserted one */
    while ((cache_pq_size(c->pq) >= c->max_entries) ||
            ((c->current_size + c->size_entry(entry)) > c->max_size)) {

        ejected = cache_pq_pop(c->pq);
        /* FIX: If ejected is NULL, we'll segfault here */
        priority = c->get_pri(ejected);

        if (c->queue_clock > priority)
            c->queue_clock = priority;

        cache_hash_set(c->ht,
                       c->key_entry(ejected),
                       CACHE_HASH_KEY_STRING,
                       NULL);

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL, "Cache Purge of %s",c->key_entry(ejected));
        c->current_size -= c->size_entry(ejected);
        c->free_entry(ejected);
        c->total_purges++;
    }
    c->current_size += c->size_entry(entry);

    cache_pq_insert(c->pq, entry);
    cache_hash_set(c->ht, c->key_entry(entry), CACHE_HASH_KEY_STRING, entry);
}