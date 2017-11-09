apr_status_t cache_generate_key_default(request_rec *r, apr_pool_t* p,
                                        const char **key)
{
    /* In early processing (quick-handler, forward proxy), we want the initial
     * query-string from r->parsed_uri, since any change before CACHE_SAVE
     * shouldn't modify the key. Otherwise we want the actual query-string.
     */
    const char *path = r->uri;
    const char *query = r->args;
    if (cache_use_early_url(r)) {
        path = r->parsed_uri.path;
        query = r->parsed_uri.query;
    }
    return cache_canonicalise_key(r, p, path, query, &r->parsed_uri, key);
}