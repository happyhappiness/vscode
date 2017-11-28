void
Store::Disks::sync()
{
    for (int i = 0; i < Config.cacheSwap.n_configured; ++i)
        store(i)->sync();
}