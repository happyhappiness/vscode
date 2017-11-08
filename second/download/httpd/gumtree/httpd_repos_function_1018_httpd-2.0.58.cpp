static cacheentry *cache_tlb_lookup(cachetlbentry *tlb, cacheentry *elt,
                                    char *key)
{
    int ix = cache_tlb_hash(key);
    int i;
    int j;

    for (i=0; i < CACHE_TLB_COLS; ++i) {
        j = tlb[ix].t[i];
        if (j < 0)
            return NULL;
        if (strcmp(elt[j].key, key) == 0)
            return &elt[j];
    }
    return NULL;
}