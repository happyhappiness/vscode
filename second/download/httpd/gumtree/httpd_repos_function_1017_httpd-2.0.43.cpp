static char *get_cache_string(cache *c, const char *res, int mode,
                              apr_time_t t, char *key)
{
    cacheentry *ce;

    ce = retrieve_cache_string(c, res, key);
    if (ce == NULL) {
        return NULL;
    }
    if (mode & CACHEMODE_TS) {
        if (t != ce->time) {
            return NULL;
        }
    }
    else if (mode & CACHEMODE_TTL) {
        if (t > ce->time) {
            return NULL;
        }
    }
    return apr_pstrdup(c->pool, ce->value);
}