uint64_t
StoreHashIndex::maxSize() const
{
    uint64_t result = 0;

    for (int i = 0; i < Config.cacheSwap.n_configured; i++)
        result += store(i)->maxSize();

    return result;
}