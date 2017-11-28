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