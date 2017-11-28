void
MemStore::init()
{
    const int64_t entryLimit = EntryLimit();
    if (entryLimit <= 0)
        return; // no memory cache configured or a misconfiguration

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

    map = new MemStoreMap(ShmLabel);
    map->cleaner = this;
}