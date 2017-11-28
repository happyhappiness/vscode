StoreEntry *
Rock::SwapDir::get(const cache_key *key)
{
    if (!map || !theFile || !theFile->canRead())
        return NULL;

    sfileno filen;
    const Ipc::StoreMapSlot *const slot = map->openForReading(key, filen);
    if (!slot)
        return NULL;

    const Ipc::StoreMapSlot::Basics &basics = slot->basics;

    // create a brand new store entry and initialize it with stored basics
    StoreEntry *e = new StoreEntry();
    e->lock_count = 0;
    e->swap_dirn = index;
    e->swap_filen = filen;
    e->swap_file_sz = basics.swap_file_sz;
    e->lastref = basics.lastref;
    e->timestamp = basics.timestamp;
    e->expires = basics.expires;
    e->lastmod = basics.lastmod;
    e->refcount = basics.refcount;
    e->flags = basics.flags;
    e->store_status = STORE_OK;
    e->setMemStatus(NOT_IN_MEMORY);
    e->swap_status = SWAPOUT_DONE;
    e->ping_status = PING_NONE;
    EBIT_SET(e->flags, ENTRY_CACHABLE);
    EBIT_CLR(e->flags, RELEASE_REQUEST);
    EBIT_CLR(e->flags, KEY_PRIVATE);
    EBIT_SET(e->flags, ENTRY_VALIDATED);
    e->hashInsert(key);
    trackReferences(*e);

    return e;
    // the disk entry remains open for reading, protected from modifications
}