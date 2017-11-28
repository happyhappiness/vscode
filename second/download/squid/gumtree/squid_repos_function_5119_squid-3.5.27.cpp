StoreEntry *
Rock::SwapDir::get(const cache_key *key)
{
    if (!map || !theFile || !theFile->canRead())
        return NULL;

    sfileno filen;
    const Ipc::StoreMapAnchor *const slot = map->openForReading(key, filen);
    if (!slot)
        return NULL;

    // create a brand new store entry and initialize it with stored basics
    StoreEntry *e = new StoreEntry();
    anchorEntry(*e, filen, *slot);

    e->hashInsert(key);
    trackReferences(*e);

    return e;
    // the disk entry remains open for reading, protected from modifications
}