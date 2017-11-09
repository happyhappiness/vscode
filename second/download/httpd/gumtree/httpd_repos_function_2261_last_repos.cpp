void h2_ihash_remove_val(h2_ihash_t *ih, void *val)
{
    int id = *((int*)((char *)val + ih->ioff));
    apr_hash_set(ih->hash, &id, sizeof(id), NULL);
}