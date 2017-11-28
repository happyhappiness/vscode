void
DiskThreadsIOStrategy::registerWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("squidaio_counts", "Async IO Function Counters",
                   aioStats, 0, 1);
}