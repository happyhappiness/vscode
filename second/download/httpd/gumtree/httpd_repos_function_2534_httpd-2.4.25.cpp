int h2_proxy_ihash_empty(h2_proxy_ihash_t *ih)
{
    return apr_hash_count(ih->hash) == 0;
}