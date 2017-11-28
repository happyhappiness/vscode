void
MemStore::updateHeaders(StoreEntry *updatedE)
{
    if (!map)
        return;

    Ipc::StoreMapUpdate update(updatedE);
    assert(updatedE);
    assert(updatedE->mem_obj);
    if (!map->openForUpdating(update, updatedE->mem_obj->memCache.index))
        return;

    try {
        updateHeadersOrThrow(update);
    } catch (const std::exception &ex) {
        debugs(20, 2, "error starting to update entry " << *updatedE << ": " << ex.what());
        map->abortUpdating(update);
    }
}