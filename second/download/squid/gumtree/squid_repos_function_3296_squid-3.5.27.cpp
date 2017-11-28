void
MemStore::markForUnlink(StoreEntry &e)
{
    assert(e.mem_obj);
    if (e.mem_obj->memCache.index >= 0)
        map->freeEntry(e.mem_obj->memCache.index);
}