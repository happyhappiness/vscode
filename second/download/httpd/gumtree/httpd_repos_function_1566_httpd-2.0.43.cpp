int cache_remove_url(request_rec *r, const char *types, char *url)
{
    const char *next = types;
    const char *type;
    apr_status_t rv;
    char *key;

    rv = cache_generate_key(r,r->pool,&key);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    /* for each specified cache type, delete the URL */
    while(next) {
        type = ap_cache_tokstr(r->pool, next, &next);
        cache_run_remove_url(type, key);
    }
    return OK;
}