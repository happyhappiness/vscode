apr_status_t cache_generate_key_default(request_rec *r, apr_pool_t* p,
        const char **key)
{
    /* We want the actual query-string, which may differ from
     * r->parsed_uri.query (immutable), so use "" (not NULL).
     */
    const char *args = r->args ? r->args : "";
    return cache_canonicalise_key(r, p, r->uri, args, &r->parsed_uri, key);
}