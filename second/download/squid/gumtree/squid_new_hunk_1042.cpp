    } while (squidaio_sync());

    debugs(32, 2, "aioSync: done");
}

DiskThreadsIOStrategy::DiskThreadsIOStrategy() :
    initialised(false)
{}

void
DiskThreadsIOStrategy::aioStats(StoreEntry * sentry)
{
    storeAppendPrintf(sentry, "ASYNC IO Counters:\n");
