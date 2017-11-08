static apr_hash_entry_t **alloc_array(apr_hash_t *ht, unsigned int max)
{
   return apr_pcalloc(ht->pool, sizeof(*ht->array) * (max + 1));
}