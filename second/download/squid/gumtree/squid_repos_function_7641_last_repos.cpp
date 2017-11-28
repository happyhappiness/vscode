hash_table *
hash_create(HASHCMP * cmp_func, int hash_sz, HASHHASH * hash_func)
{
    hash_table *hid = (hash_table *)xcalloc(1, sizeof(hash_table));
    if (!hash_sz)
        hid->size = (unsigned int) DEFAULT_HASH_SIZE;
    else
        hid->size = (unsigned int) hash_sz;
    /* allocate and null the buckets */
    hid->buckets = (hash_link **)xcalloc(hid->size, sizeof(hash_link *));
    hid->cmp = cmp_func;
    hid->hash = hash_func;
    hid->next = NULL;
    hid->current_slot = 0;
    return hid;
}