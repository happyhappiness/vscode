static cache_hash_entry_t **alloc_array(cache_hash_t *ht, int max)
{
   return calloc(1, sizeof(*ht->array) * (max + 1));
}