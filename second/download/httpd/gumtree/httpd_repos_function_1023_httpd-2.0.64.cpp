static void set_cache_string(cache *c, const char *res, int mode, apr_time_t t,
                             char *key, char *value)
{
    cacheentry ce;

    ce.time  = t;
    ce.key   = key;
    ce.value = value;
    store_cache_string(c, res, &ce);
    return;
}