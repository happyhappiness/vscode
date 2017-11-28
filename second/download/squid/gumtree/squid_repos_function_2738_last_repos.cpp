void
MemStore::unlink(StoreEntry &e)
{
    if (e.mem_obj && e.mem_obj->memCache.index >= 0) {
        map->freeEntry(e.mem_obj->memCache.index);
        disconnect(e);
    } else if (map) {
        // the entry may have been loaded and then disconnected from the cache
        map->freeEntryByKey(reinterpret_cast<cache_key*>(e.key));
    }

    e.destroyMemObject(); // XXX: but it may contain useful info such as a client list. The old code used to do that though, right?
}