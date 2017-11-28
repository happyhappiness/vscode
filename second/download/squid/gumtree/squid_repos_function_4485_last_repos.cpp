void
Store::Disk::getStats(StoreInfoStats &stats) const
{
    if (!doReportStat())
        return;

    stats.swap.size = currentSize();
    stats.swap.capacity = maxSize();
    stats.swap.count = currentCount();
}