hash_link *
hash_lookup(hash_table * hid, const void *k)
{
    hash_link *walker;
    int b;
    PROF_start(hash_lookup);
    assert(k != NULL);
    b = hid->hash(k, hid->size);
    for (walker = hid->buckets[b]; walker != NULL; walker = walker->next) {
        if ((hid->cmp) (k, walker->key) == 0) {
            PROF_stop(hash_lookup);
            return (walker);
        }
        assert(walker != walker->next);
    }
    PROF_stop(hash_lookup);
    return NULL;
}