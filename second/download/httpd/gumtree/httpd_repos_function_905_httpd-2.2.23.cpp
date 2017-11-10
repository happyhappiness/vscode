void cache_hash_free(cache_hash_t *ht)
{
    if (ht) {
        if (ht->array) {
            free (ht->array);
        }
        free (ht);
    }
}