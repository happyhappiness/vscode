void h2_ihash_clear(h2_ihash_t *ih)
{
    apr_hash_clear(ih->hash);
}