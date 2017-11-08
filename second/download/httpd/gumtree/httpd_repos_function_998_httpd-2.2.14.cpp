void* cache_find(cache_cache_t* c, const char *key)
{
    return cache_hash_get(c->ht, key, CACHE_HASH_KEY_STRING);
}