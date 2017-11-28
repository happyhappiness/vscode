void
Store::Disks::getStats(StoreInfoStats &stats) const
{
    // accumulate per-disk cache stats
    for (int i = 0; i < Config.cacheSwap.n_configured; ++i) {
        StoreInfoStats dirStats;
        store(i)->getStats(dirStats);
        stats += dirStats;
    }

    // common to all disks
    stats.swap.open_disk_fd = store_open_disk_fd;

    // memory cache stats are collected in StoreController::getStats(), for now
}