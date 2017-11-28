void
MemStore::init()
{
    const int64_t entryLimit = EntryLimit();
    if (entryLimit <= 0)
        return; // no memory cache configured or a misconfiguration

    // check compatibility with the disk cache, if any
    if (Config.cacheSwap.n_configured > 0) {
        const int64_t diskMaxSize = Store::Root().maxObjectSize();
        const int64_t memMaxSize = maxObjectSize();
        if (diskMaxSize == -1) {
            debugs(20, DBG_IMPORTANT, "WARNING: disk-cache maximum object size "
                   "is unlimited but mem-cache maximum object size is " <<
                   memMaxSize / 1024.0 << " KB");
        } else if (diskMaxSize > memMaxSize) {
            debugs(20, DBG_IMPORTANT, "WARNING: disk-cache maximum object size "
                   "is too large for mem-cache: " <<
                   diskMaxSize / 1024.0 << " KB > " <<
                   memMaxSize / 1024.0 << " KB");
        }
    }

    freeSlots = shm_old(Ipc::Mem::PageStack)(SpaceLabel);
    extras = shm_old(Extras)(ExtrasLabel);

    Must(!map);
    map = new MemStoreMap(MapLabel);
    map->cleaner = this;
}