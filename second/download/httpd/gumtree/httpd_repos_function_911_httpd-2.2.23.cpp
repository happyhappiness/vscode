void* cache_hash_set(cache_hash_t *ht,
                                     const void *key,
                                     apr_ssize_t klen,
                                     const void *val)
{
    cache_hash_entry_t **hep, *tmp;
    const void *tval;
    hep = find_entry(ht, key, klen, val);
    /* If hep == NULL, then the malloc() in find_entry failed */
    if (hep && *hep) {
        if (!val) {
            /* delete entry */
            tval = (*hep)->val;
            tmp = *hep;
            *hep = (*hep)->next;
            free(tmp);
            --ht->count;
        }
        else {
            /* replace entry */
            tval = (*hep)->val;
            (*hep)->val = val;
        }
        /* Return the object just removed from the cache to let the
         * caller clean it up. Cast the constness away upon return.
         */
        return (void *) tval;
    }
    /* else key not present and val==NULL */
    return NULL;
}