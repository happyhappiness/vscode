cache_hash_t* cache_hash_make(apr_size_t size)
{
    cache_hash_t *ht;
    ht = malloc(sizeof(cache_hash_t));
    if (!ht) {
        return NULL;
    }
    ht->count = 0;
    ht->max = size;
    ht->array = alloc_array(ht, ht->max);
    if (!ht->array) {
        free(ht);
        return NULL;
    }
    return ht;
}