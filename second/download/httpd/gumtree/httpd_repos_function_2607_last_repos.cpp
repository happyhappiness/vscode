void h2_proxy_ihash_add(h2_proxy_ihash_t *ih, void *val)
{
    apr_hash_set(ih->hash, ((char *)val + ih->ioff), sizeof(int), val);
}