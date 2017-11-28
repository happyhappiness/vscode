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