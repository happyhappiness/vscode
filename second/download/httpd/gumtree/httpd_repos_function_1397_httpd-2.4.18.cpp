apr_status_t cache_generate_key_default(request_rec *r, apr_pool_t* p,
        const char **key)
{
    return cache_canonicalise_key(r, p, r->uri, &r->parsed_uri, key);
}