apr_status_t cache_remove(cache_cache_t *c, void *entry)
{
    apr_size_t entry_size = c->size_entry(entry);
    apr_status_t rc;
    rc = cache_pq_remove(c->pq, entry);
    if (rc != APR_SUCCESS)
        return rc;

    cache_hash_set(c->ht, c->key_entry(entry), CACHE_HASH_KEY_STRING, NULL);
    c->current_size -= entry_size;

    return APR_SUCCESS;
}