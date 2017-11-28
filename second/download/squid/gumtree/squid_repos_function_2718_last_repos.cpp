StoreEntry *
MemStore::get(const cache_key *key)
{
    if (!map)
        return NULL;

    sfileno index;
    const Ipc::StoreMapAnchor *const slot = map->openForReading(key, index);
    if (!slot)
        return NULL;

    // create a brand new store entry and initialize it with stored info
    StoreEntry *e = new StoreEntry();

    // XXX: We do not know the URLs yet, only the key, but we need to parse and
    // store the response for the Root().get() callers to be happy because they
    // expect IN_MEMORY entries to already have the response headers and body.
    e->makeMemObject();

    anchorEntry(*e, index, *slot);

    const bool copied = copyFromShm(*e, index, *slot);

    if (copied) {
        e->hashInsert(key);
        return e;
    }

    debugs(20, 3, HERE << "mem-loading failed; freeing " << index);
    map->freeEntry(index); // do not let others into the same trap
    return NULL;
}