int64_t
MemStore::EntryLimit()
{
    if (!Config.memShared || !Config.memMaxSize)
        return 0; // no memory cache configured

    const int64_t minEntrySize = Ipc::Mem::PageSize();
    const int64_t entryLimit = Config.memMaxSize / minEntrySize;
    return entryLimit;
}