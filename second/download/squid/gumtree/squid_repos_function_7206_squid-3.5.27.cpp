heap_key
HeapKeyGen_StoreEntry_GDSF(void *entry, double heap_age)
{
    StoreEntry *e = (StoreEntry *)entry;
    heap_key key;
    double size = e->swap_file_sz ? (double) e->swap_file_sz : 1.0;
    double tie = (e->lastref > 1) ? (1.0 / e->lastref) : 1.0;
    key = heap_age + ((double) e->refcount / size) - tie;
    debugs(81, 3, "HeapKeyGen_StoreEntry_GDSF: " << e->getMD5Text() <<
           " size=" << size << " refcnt=" << e->refcount << " lastref=" <<
           e->lastref << " heap_age=" << heap_age << " tie=" << tie <<
           " -> " << key);

    if (e->mem_obj)
        debugs(81, 3, "storeId=" << e->mem_obj->storeId());

    return key;
}