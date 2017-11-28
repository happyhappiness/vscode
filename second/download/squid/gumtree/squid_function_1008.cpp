void
DiskThreadsIOStrategy::aioStats(StoreEntry * sentry)
{
    storeAppendPrintf(sentry, "ASYNC IO Counters:\n");
    storeAppendPrintf(sentry, "Operation\t# Requests\tNumber serviced\n");
    storeAppendPrintf(sentry, "open\t%d\t%d\n", squidaio_counts.open_start, squidaio_counts.open_finish);
    storeAppendPrintf(sentry, "close\t%d\t%d\n", squidaio_counts.close_start, squidaio_counts.close_finish);
    storeAppendPrintf(sentry, "cancel\t%d\t-\n", squidaio_counts.cancel);
    storeAppendPrintf(sentry, "write\t%d\t%d\n", squidaio_counts.write_start, squidaio_counts.write_finish);
    storeAppendPrintf(sentry, "read\t%d\t%d\n", squidaio_counts.read_start, squidaio_counts.read_finish);
    storeAppendPrintf(sentry, "stat\t%d\t%d\n", squidaio_counts.stat_start, squidaio_counts.stat_finish);
    storeAppendPrintf(sentry, "unlink\t%d\t%d\n", squidaio_counts.unlink_start, squidaio_counts.unlink_finish);
    storeAppendPrintf(sentry, "check_callback\t%d\t-\n", squidaio_counts.check_callback);
    storeAppendPrintf(sentry, "queue\t%d\t-\n", squidaio_get_queue_len());
    squidaio_stats(sentry);
}