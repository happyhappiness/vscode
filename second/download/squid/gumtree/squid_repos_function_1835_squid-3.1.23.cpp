void
storeIOStats(StoreEntry * sentry)
{
    storeAppendPrintf(sentry, "Store IO Interface Stats\n");
    storeAppendPrintf(sentry, "create.calls %d\n", store_io_stats.create.calls);
    storeAppendPrintf(sentry, "create.select_fail %d\n", store_io_stats.create.select_fail);
    storeAppendPrintf(sentry, "create.create_fail %d\n", store_io_stats.create.create_fail);
    storeAppendPrintf(sentry, "create.success %d\n", store_io_stats.create.success);
}