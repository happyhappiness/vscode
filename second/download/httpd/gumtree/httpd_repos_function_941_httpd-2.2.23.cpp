static const char* memcache_cache_get_key(void*a)
{
    cache_object_t *obj = (cache_object_t *)a;
    return obj->key;
}