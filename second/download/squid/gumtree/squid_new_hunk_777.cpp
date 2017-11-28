
/* Flush all pending I/O */
void
DiskThreadsIOStrategy::sync()
{
    if (!initialised)
        return;         /* nothing to do then */

    /* Flush all pending operations */
    debugs(32, 2, "aioSync: flushing pending I/O operations");

    do {
        callback();
    } while (squidaio_sync());

    debugs(32, 2, "aioSync: done");
}

DiskThreadsIOStrategy::DiskThreadsIOStrategy() :
    initialised(false),
    squidaio_ctrl_pool(NULL)
{}

void
DiskThreadsIOStrategy::aioStats(StoreEntry * sentry)
{
    storeAppendPrintf(sentry, "ASYNC IO Counters:\n");
    storeAppendPrintf(sentry, "  Operation\t# Requests\tNumber serviced\n");
    storeAppendPrintf(sentry, "  open\t%" PRIu64 "\t%" PRIu64 "\n", squidaio_counts.open_start, squidaio_counts.open_finish);
    storeAppendPrintf(sentry, "  close\t%" PRIu64 "\t%" PRIu64 "\n", squidaio_counts.close_start, squidaio_counts.close_finish);
    storeAppendPrintf(sentry, "  cancel\t%" PRIu64 "\t-\n", squidaio_counts.cancel);
    storeAppendPrintf(sentry, "  write\t%" PRIu64 "\t%" PRIu64 "\n", squidaio_counts.write_start, squidaio_counts.write_finish);
    storeAppendPrintf(sentry, "  read\t%" PRIu64 "\t%" PRIu64 "\n", squidaio_counts.read_start, squidaio_counts.read_finish);
    storeAppendPrintf(sentry, "  stat\t%" PRIu64 "\t%" PRIu64 "\n", squidaio_counts.stat_start, squidaio_counts.stat_finish);
    storeAppendPrintf(sentry, "  unlink\t%" PRIu64 "\t%" PRIu64 "\n", squidaio_counts.unlink_start, squidaio_counts.unlink_finish);
    storeAppendPrintf(sentry, "  check_callback\t%" PRIu64 "\t-\n", squidaio_counts.check_callback);
    storeAppendPrintf(sentry, "  queue\t%d\t-\n", squidaio_get_queue_len());
    squidaio_stats(sentry);
}

DiskThreadsIOStrategy DiskThreadsIOStrategy::Instance;
bool
DiskThreadsIOStrategy::shedLoad()
