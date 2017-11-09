void h2_proxy_ihash_remove(h2_proxy_ihash_t *ih, int id)
{
    apr_hash_set(ih->hash, &id, sizeof(id), NULL);
}