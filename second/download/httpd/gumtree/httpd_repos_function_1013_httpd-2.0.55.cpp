static void cache_tlb_replace(cachetlbentry *tlb, cacheentry *elt,
                              cacheentry *e)
{
    int ix = cache_tlb_hash(e->key);
    int i;

    tlb = &tlb[ix];

    for (i=1; i < CACHE_TLB_COLS; ++i)
        tlb->t[i] = tlb->t[i-1];

    tlb->t[0] = e - elt;
}