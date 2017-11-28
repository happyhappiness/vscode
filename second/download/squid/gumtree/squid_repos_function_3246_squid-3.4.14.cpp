StoreEntry *
MemStore::get(const cache_key *key)
{
    if (!map)
        return NULL;

    // XXX: replace sfileno with a bigger word (sfileno is only for cache_dirs)
    sfileno index;
    const Ipc::StoreMapSlot *const slot = map->openForReading(key, index);
    if (!slot)
        return NULL;

    const Ipc::StoreMapSlot::Basics &basics = slot->basics;
    const MemStoreMap::Extras &extras = map->extras(index);

    // create a brand new store entry and initialize it with stored info
    StoreEntry *e = new StoreEntry();
    e->lock_count = 0;

    e->swap_file_sz = basics.swap_file_sz;
    e->lastref = basics.lastref;
    e->timestamp = basics.timestamp;
    e->expires = basics.expires;
    e->lastmod = basics.lastmod;
    e->refcount = basics.refcount;
    e->flags = basics.flags;

    e->store_status = STORE_OK;
    e->mem_status = IN_MEMORY; // setMemStatus(IN_MEMORY) requires mem_obj
    //e->swap_status = set in StoreEntry constructor to SWAPOUT_NONE;
    e->ping_status = PING_NONE;

    EBIT_SET(e->flags, ENTRY_CACHABLE);
    EBIT_CLR(e->flags, RELEASE_REQUEST);
    EBIT_CLR(e->flags, KEY_PRIVATE);
    EBIT_SET(e->flags, ENTRY_VALIDATED);

    const bool copied = copyFromShm(*e, extras);

    // we copied everything we could to local memory; no more need to lock
    map->closeForReading(index);

    if (copied) {
        e->hashInsert(key);
        return e;
    }

    debugs(20, 3, HERE << "mem-loading failed; freeing " << index);
    map->free(index); // do not let others into the same trap
    return NULL;
}