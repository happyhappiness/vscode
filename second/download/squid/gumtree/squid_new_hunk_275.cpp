        *
         * Step 1: make the store rebuilds use a search internally
        * Step 2: change the search logic to use the four modes described
        *         above
        * Step 3: have the hash index walk the searches itself.
         */
        if (dir(i).active())
            store(i)->init();
    }
}

uint64_t
StoreHashIndex::maxSize() const
{
    uint64_t result = 0;

    for (int i = 0; i < Config.cacheSwap.n_configured; ++i) {
        if (dir(i).doReportStat())
            result += store(i)->maxSize();
    }

    return result;
}

uint64_t
StoreHashIndex::minSize() const
{
    uint64_t result = 0;

    for (int i = 0; i < Config.cacheSwap.n_configured; ++i) {
        if (dir(i).doReportStat())
            result += store(i)->minSize();
    }

    return result;
}

uint64_t
StoreHashIndex::currentSize() const
{
    uint64_t result = 0;

    for (int i = 0; i < Config.cacheSwap.n_configured; ++i) {
        if (dir(i).doReportStat())
            result += store(i)->currentSize();
    }

    return result;
}

uint64_t
StoreHashIndex::currentCount() const
{
    uint64_t result = 0;

    for (int i = 0; i < Config.cacheSwap.n_configured; ++i) {
        if (dir(i).doReportStat())
            result += store(i)->currentCount();
    }

    return result;
}

int64_t
StoreHashIndex::maxObjectSize() const
{
    int64_t result = -1;

    for (int i = 0; i < Config.cacheSwap.n_configured; ++i) {
        if (dir(i).active() && store(i)->maxObjectSize() > result)
            result = store(i)->maxObjectSize();
    }

    return result;
}

void
StoreHashIndex::getStats(StoreInfoStats &stats) const
{
    // accumulate per-disk cache stats
    for (int i = 0; i < Config.cacheSwap.n_configured; ++i) {
        StoreInfoStats dirStats;
        store(i)->getStats(dirStats);
        stats += dirStats;
    }

    // common to all disks
    stats.swap.open_disk_fd = store_open_disk_fd;

    // memory cache stats are collected in StoreController::getStats(), for now
}

void
StoreHashIndex::stat(StoreEntry & output) const
{
    int i;

    /* Now go through each store, calling its stat routine */

    for (i = 0; i < Config.cacheSwap.n_configured; ++i) {
        storeAppendPrintf(&output, "\n");
        store(i)->stat(output);
    }
}

void
StoreHashIndex::reference(StoreEntry &e)
{
    e.store()->reference(e);
}

bool
StoreHashIndex::dereference(StoreEntry &e, bool wantsLocalMemory)
{
    return e.store()->dereference(e, wantsLocalMemory);
}

void
StoreHashIndex::maintain()
{
    int i;
    /* walk each fs */

    for (i = 0; i < Config.cacheSwap.n_configured; ++i) {
        /* XXX FixMe: This should be done "in parallell" on the different
         * cache_dirs, not one at a time.
         */
        /* call the maintain function .. */
        store(i)->maintain();
    }
}

void
StoreHashIndex::sync()
{
    for (int i = 0; i < Config.cacheSwap.n_configured; ++i)
        store(i)->sync();
}

