cache_hash_index_t* cache_hash_first(cache_hash_t *ht)
{
    cache_hash_index_t *hi;

    hi = &ht->iterator;
    hi->ht = ht;
    hi->index = 0;
    hi->this = NULL;
    hi->next = NULL;
    return cache_hash_next(hi);
}