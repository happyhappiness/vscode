int h2_ihash_is_empty(h2_ihash_t *ih)
{
    return apr_hash_count(ih->hash) == 0;
}