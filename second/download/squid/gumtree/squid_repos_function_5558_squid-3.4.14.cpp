void
DiskThreadsIOStrategy::registerWithCacheManager(void)
{
    Mgr::RegisterAction("squidaio_counts", "Async IO Function Counters",
                        aioStats, 0, 1);
}