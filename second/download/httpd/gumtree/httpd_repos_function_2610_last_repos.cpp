void h2_proxy_ihash_clear(h2_proxy_ihash_t *ih)
{
    apr_hash_clear(ih->hash);
}