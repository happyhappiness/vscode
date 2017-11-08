void* cache_hash_get(cache_hash_t *ht,
                                   const void *key,
                                   apr_ssize_t klen)
{
    cache_hash_entry_t *he;
    he = *find_entry(ht, key, klen, NULL);
    if (he)
        return (void *)he->val;
    else
        return NULL;
}