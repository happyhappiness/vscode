int64_t
MemStore::EntryLimit()
{
    if (!Config.memShared || !Config.memMaxSize)
        return 0; // no memory cache configured

    const int64_t entrySize = Ipc::Mem::PageSize(); // for now
    const int64_t entryLimit = Config.memMaxSize / entrySize;
    return entryLimit;
}