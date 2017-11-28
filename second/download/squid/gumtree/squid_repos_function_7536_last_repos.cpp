heap_key
HeapKeyGen_StoreEntry_LFUDA(void *entry, double heap_age)
{
    StoreEntry *e = (StoreEntry *)entry;
    heap_key key;
    double tie;

    if (e->lastref <= 0)
        tie = 0.0;
    else if (squid_curtime <= e->lastref)
        tie = 0.0;
    else
        tie = 1.0 - exp((double) (e->lastref - squid_curtime) / 86400.0);

    key = heap_age + (double) e->refcount - tie;

    debugs(81, 3, "HeapKeyGen_StoreEntry_LFUDA: " << e->getMD5Text() <<
           " refcnt=" << e->refcount << " lastref=" << e->lastref <<
           " heap_age=" << heap_age << " tie=" << tie << " -> " << key);

    if (e->mem_obj)
        debugs(81, 3, "storeId=" << e->mem_obj->storeId());

    return (double) key;
}