heap_key
HeapKeyGen_StoreEntry_LRU(void *entry, double heap_age)
{
    StoreEntry *e = (StoreEntry *)entry;
    debugs(81, 3, "HeapKeyGen_StoreEntry_LRU: " <<
           e->getMD5Text() << " heap_age=" << heap_age <<
           " lastref=" << (double) e->lastref  );

    if (e->mem_obj && e->mem_obj->url)
        debugs(81, 3, "HeapKeyGen_StoreEntry_LRU: url=" << e->mem_obj->url);

    return (heap_key) e->lastref;
}