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