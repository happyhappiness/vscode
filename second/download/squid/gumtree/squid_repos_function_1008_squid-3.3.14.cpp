static void
update_maxobjsize(void)
{
    int64_t ms = -1;

    // determine the maximum size object that can be stored to disk
    for (int i = 0; i < Config.cacheSwap.n_configured; ++i) {
        assert (Config.cacheSwap.swapDirs[i].getRaw());

        const int64_t storeMax = dynamic_cast<SwapDir *>(Config.cacheSwap.swapDirs[i].getRaw())->maxObjectSize();
        if (ms < storeMax)
            ms = storeMax;
    }

    // Ensure that we do not discard objects which could be stored only in memory.
    // It is governed by maximum_object_size_in_memory (for now)
    // TODO: update this to check each in-memory location (SMP and local memory limits differ)
    if (ms < static_cast<int64_t>(Config.Store.maxInMemObjSize))
        ms = Config.Store.maxInMemObjSize;

    store_maxobjsize = ms;
}