void
MemStore::keep(StoreEntry &e)
{
    if (!map) {
        debugs(20, 5, HERE << "No map to mem-cache " << e);
        return;
    }

    sfileno index = 0;
    Ipc::StoreMapSlot *slot = map->openForWriting(reinterpret_cast<const cache_key *>(e.key), index);
    if (!slot) {
        debugs(20, 5, HERE << "No room in mem-cache map to index " << e);
        return;
    }

    MemStoreMap::Extras &extras = map->extras(index);
    if (copyToShm(e, extras)) {
        slot->set(e);
        map->closeForWriting(index, false);
    } else {
        map->abortIo(index);
    }
}