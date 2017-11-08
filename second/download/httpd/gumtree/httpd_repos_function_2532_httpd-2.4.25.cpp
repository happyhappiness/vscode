h2_proxy_ihash_t *h2_proxy_ihash_create(apr_pool_t *pool, size_t offset_of_int)
{
    h2_proxy_ihash_t *ih = apr_pcalloc(pool, sizeof(h2_proxy_ihash_t));
    ih->hash = apr_hash_make_custom(pool, ihash);
    ih->ioff = offset_of_int;
    return ih;
}