void MemStoreRr::create(const RunnerRegistry &)
{
    if (!Config.memShared)
        return;

    Must(!owner);
    const int64_t entryLimit = MemStore::EntryLimit();
    if (entryLimit <= 0) {
        if (Config.memMaxSize > 0) {
            debugs(20, DBG_IMPORTANT, "WARNING: mem-cache size is too small ("
                   << (Config.memMaxSize / 1024.0) << " KB), should be >= " <<
                   (Ipc::Mem::PageSize() / 1024.0) << " KB");
        }
        return; // no memory cache configured or a misconfiguration
    }
    owner = MemStoreMap::Init(ShmLabel, entryLimit);
}