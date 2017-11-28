static int64_t
storeCalcMaxObjSize()
{
    int64_t ms = 0; // nothing can be cached without at least one store consent

    // global maximum is at least the disk store maximum
    for (int i = 0; i < Config.cacheSwap.n_configured; ++i) {
        assert (Config.cacheSwap.swapDirs[i].getRaw());
        const int64_t storeMax = dynamic_cast<SwapDir *>(Config.cacheSwap.swapDirs[i].getRaw())->maxObjectSize();
        if (ms < storeMax)
            ms = storeMax;
    }

    // global maximum is at least the memory store maximum
    // TODO: move this into a memory cache class when we have one
    const int64_t memMax = static_cast<int64_t>(min(Config.Store.maxInMemObjSize, Config.memMaxSize));
    if (ms < memMax)
        ms = memMax;

    return ms;
}