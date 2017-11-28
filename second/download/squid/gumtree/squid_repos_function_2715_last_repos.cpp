int64_t
MemStore::maxObjectSize() const
{
    return min(Config.Store.maxInMemObjSize, Config.memMaxSize);
}