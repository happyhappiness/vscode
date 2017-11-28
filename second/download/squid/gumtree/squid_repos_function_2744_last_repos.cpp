void
MemStoreRr::create()
{
    if (!Config.memShared)
        return;

    const int64_t entryLimit = MemStore::EntryLimit();
    if (entryLimit <= 0) {
        if (Config.memMaxSize > 0) {
            debugs(20, DBG_IMPORTANT, "WARNING: mem-cache size is too small ("
                   << (Config.memMaxSize / 1024.0) << " KB), should be >= " <<
                   (Ipc::Mem::PageSize() / 1024.0) << " KB");
        }
        return; // no memory cache configured or a misconfiguration
    }

    Must(!spaceOwner);
    spaceOwner = shm_new(Ipc::Mem::PageStack)(SpaceLabel, SpacePoolId,
                 entryLimit, 0);
    Must(!mapOwner);
    mapOwner = MemStoreMap::Init(MapLabel, entryLimit);
    Must(!extrasOwner);
    extrasOwner = shm_new(MemStoreMapExtras)(ExtrasLabel, entryLimit);
}