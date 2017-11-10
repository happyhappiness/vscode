size_t h2_ihash_count(h2_ihash_t *ih)
{
    return apr_hash_count(ih->hash);
}