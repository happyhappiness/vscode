void
StoreHashIndex::create()
{
    for (int i = 0; i < Config.cacheSwap.n_configured; i++)
        store(i)->create();
}