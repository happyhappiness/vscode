void *h2_ihash_get(h2_ihash_t *ih, int id)
{
    return apr_hash_get(ih->hash, &id, sizeof(id));
}